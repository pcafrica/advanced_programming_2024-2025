#!/usr/bin/env python3

from time import time

class Polynomial:
    def __init__(self, *coefficients):
        self.coefficients = coefficients

    @classmethod
    def from_string(cls, poly_str):
        terms = poly_str.split("+")
        coefficients = [int(term.split("x")[0]) for term in terms]
        return cls(*coefficients)

    def __repr__(self):
        pass

    def __add__(self, other):
        pass

    def __mul__(self, other):
        pass

    
class StandardPolynomialEvaluator(Polynomial):
    pass

class HornerPolynomialEvaluator(Polynomial):
    pass

def evaluate_polynomial(poly_evaluator, x_list):
    return poly_evaluator.evaluate(x_list)

poly1 = Polynomial(1, 2, 3)
poly2 = Polynomial(2, 3, 4)
print(poly1)
print(poly2)

poly3 = Polynomial.from_string("1 + 2x + 3x^2")
print(poly3, '\n')
