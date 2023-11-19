#!/usr/bin/env python3
import requests
import time
import random

enqueue_url = "http://127.0.0.1:8080/?enqueue="
dequeue_url = "http://127.0.0.1:8080/?dequeue"
num = 1_000_000
rounds = 0


s = requests.Session()
while True:
    rounds += 1

    print("round " + str(rounds) + " enqueing " + str(num) + " values")
    timing = time.time()
    for i in range(num):
        s.get(enqueue_url + str(random.getrandbits(64)))
    print("took " + str(time.time() - timing) + " seconds")

    print("round " + str(rounds) + " dequeing " + str(num) + " values")
    timing = time.time()
    for i in range(num):
        s.get(dequeue_url)
    print("took " + str(time.time() - timing) + " seconds")

    print()