import statistics
import sys

def main():
    if len(sys.argv) < 2:
        return
    
    fp = open(sys.argv[1], "r")
    line = fp.readline()
    arr = []
    arr.append(float(line))
    while line:
        line = fp.readline()
        if line:
            arr.append(float(line))
    
    print( str(min(arr)) + ' | ' + str(max(arr)) + ' | ' + str(statistics.mean(arr)) + ' | '+ str(statistics.stdev(arr)))


if __name__ == "__main__":
    main()