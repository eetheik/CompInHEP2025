#!/usr/bin/python3
import regex as re

def exercise2():
    totrecorded_re = re.compile(r"\|\s+\d+\s+\|\s+\d+\s+\|\s+\d+\s+\|\s+\d+\s+\|\s+\d+.\d+\s+\|\s+(?P<totrecorded>\d+.\d+)\s+\|")

    with open("../../../brilcalc.log", "r") as brilcalc:
        brilcalc_content = brilcalc.read()

    totrecorded_pb = float(re.search(totrecorded_re, brilcalc_content).group("totrecorded"))
    totrecorded_fb = totrecorded_pb*1e-3 # Inverse femtobarns so conversion rate also inversed
    print(f"Exercise 2) totrecorded (/fb): {totrecorded_fb:.1f}")

def exercise3():
    recorded_re = re.compile(r"\|\s+\d+:\d+\s+\|\s+\d+/\d+/\d+\s+\d+:\d+:\d+\s+\|\s+\d+\s+\|\s+\d+\s+\|\s+\d+.\d+\s+\|\s+(?P<recorded>\d+.\d+)\s+\|")
    
    with open("../../../brilcalc.log", "r") as brilcalc:
        brilcalc_content = brilcalc.read()
    
    recorded_pb = [float(i) for i in re.findall(recorded_re, brilcalc_content)]
    sum_recorded_fb = sum(recorded_pb)*1e-3
    print(f"Exercise 3) sum of recorded (/fb): {sum_recorded_fb:.1f}")

exercise2()
exercise3()