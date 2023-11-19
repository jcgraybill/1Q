#include <iostream>
#include <unistd.h>
#include <map>
#include <sstream>

#include "1q.h"
#include "queue_form.h"
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

using namespace std;

int main (void)
{
    uint64_t count = 0;
    long pid = getpid();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0)
    {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);
        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        const char * query_string = FCGX_GetParam("QUERY_STRING", request.envp);

        std::map<std::string, std::string> params;
        std::string keyval, key, val;
        std::istringstream query = std::istringstream(query_string);
        
        while(std::getline(query, keyval, '&')) 
        {
                std::istringstream query(keyval);

                if (std::getline(std::getline(query, key, '='), val)) {
                        params[key] = val;
                } else {
                        params[keyval] = "";
                }
        }

        uint64_t enqueued, dequeued;
        bool did_enqueue = false;
        bool did_dequeue = false;
        bool queue_was_empty = false;
        bool enqueued_bad_value = false;
        bool pretty = false;

        for (auto const& param: params) {
                if (param.first == "enqueue") {
                        try {
                                enqueued = std::stoull(param.second);
                                enqueue(enqueued);
                                did_enqueue = true;
                        } catch (std::invalid_argument const& ex) {
                                enqueued_bad_value = true;
                        } catch (std::out_of_range const& ex) {
                                enqueued_bad_value = true;
                        }
                }
                if (param.first == "dequeue") {
                        if (! queue_is_empty() ) {
                                queue_was_empty = false;
                                dequeued = dequeue();
                                did_dequeue = true;
                        } else {
                                queue_was_empty = true;
                        }
                }
                if (param.first == "pretty") {
                        pretty = true;
                }
        }

        if (queue_was_empty || enqueued_bad_value ) {
                cout << "Status: 400\r\n";
        } else {
                cout << "Status: 200\r\n";
        }
        if (! pretty ) {
                cout << "Content-Type: text/plain\r\n\r\n";
                if (did_dequeue)
                        cout << dequeued << "\n";                
        } else {
                cout << "Content-type: text/html\r\n\r\n"
                        "<html color-mode='user'><head>"
                        "<title>1Q</title>"
                        "<link rel='stylesheet' href='https://unpkg.com/mvp.css'>"
                        "</head><body><main><section>";

                cout << queue_form();

                cout << "<aside>";

                if (did_enqueue)
                        cout << "<p><b>enqueued:</b> " << enqueued << "</p>";
                
                if (did_dequeue)
                        cout << "<p><b>dequeued:</b> " << dequeued << "</p>";

                if (enqueued_bad_value) 
                        cout << "<p>can't enqueue that</p>";

                if (queue_was_empty)
                        cout << "<p>nothing to dequeue</p>";

                cout << "<p><b>length:</b> " << queue_length() << "</p>"
                        << "</aside>";

                cout << "<aside><p><b>pid:</b> " << pid << "</p>"
                <<  "<p><b>request:</b> " << ++count << "</p>";

                cout << "<p><b>params</b></p>";

                cout << "<ul>";
                for(auto const& param: params)
                        std::cout << "<li><b>" << param.first << ":</b> " << param.second << "</li>";

                cout << "</ul></aside>";

                penv(request.envp);
                cout << "</section></main></body></html>";
        }

    }
    return 0;
}