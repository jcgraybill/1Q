#include <iostream>

const char* qf = R"form(
<section>
    <form>
        <input type="number" id="enqueue" name="enqueue" size="10" placeholder="0" autofocus onfocus="this.select()">
        <input type="hidden" name="pretty" value="true">
        <button type="submit">enqueue</button>
        <a href="?dequeue&pretty"><b>dequeue</b></a>
    </form>
</section>
)form";

const char* queue_form() {
    return qf;
}

void penv(const char * const * envp)
{
    std::cout << "<details><summary>fastcgi environment</summary><pre><code>";
    for ( ; *envp; ++envp)
    {
        std::cout << *envp << "\n";
    }
    std::cout << "</code></pre></details>";
}