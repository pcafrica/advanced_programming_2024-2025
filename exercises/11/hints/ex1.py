#!/usr/bin/env python3

from math import sin

def explicit_euler(u0, h):
    u = u0
    while True:
        u = u - h * sin(u)
        yield u
