import subprocess

# Pick knot directory, Alexander grading range, & Maslov grading range
kdir = input("Enter knot name: ")
amin = int(input("Enter minimum Alexander grading: "))
amax = int(input("Enter maximum Alexander grading: "))
mmin = int(input("Enter minimum Maslov grading: "))
mmax = int(input("Enter maximum Maslov grading: "))

# Find all necessary values for running hfkm
kdir = "knots/" + kdir
hfkm = "/home/dan/Dropbox/caltech/freshman/surf/yini/current/hfk/bin/hfkm"

# Run over all ranges and save
amrks = []
for a in range(amin, amax + 1):
    mrks = []
    for m in range(mmin, mmax + 1):
        cmd = hfkm + " " + kdir + " " + str(a) + " " +  str(m)
        out = str(subprocess.check_output(cmd, shell=True))
        lines = out.split("\\n")
        for l in lines:
            if "rk H_{" in l:
                mrks.append(l.split(" ")[-1])
    amrks.append(mrks)
# Display
print
for row in amrks[::-1]:
    rowstr = ""
    for rk in row:
        rowstr += rk + "\t"
    print(rowstr)
