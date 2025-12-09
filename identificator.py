from pathlib import Path
import os

def take_caption(lines, L):
    for line in lines:
        myline = line.strip().split(",")
        if (myline[0].split(" ")[0]) == "LTEXT":
            if L[2] == myline[3]:
                caption = myline[0].split("\"")[1]
                caption = caption.replace("&", "").replace(" ", "")
                return caption

def extract():
    rc = "resources\\resource.rc"
    rh = "resources\\resource.h"
    ides = []
    tipes = ["PUSHBUTTON", "DEFPUSHBUTTON", "COMBOBOX", "LTEXT"]
    std_tipes = ["PBTN", "DPBTN", "CBX", "LT"]
    if (os.path.exists(rc)):
        with open(rc, "r") as f:
            cnt = f.read()
            par = cnt.split("BEGIN")[1]
            elements = par.split("END")[0]
            lines = elements.split("\n")
            print(lines[0])
            for line in lines:
                L = line.strip().split(",")
                if len(L) != 1:
                    iden = L[1]
                    tipe = L[0].split(" ")[0]
                    if not tipe == "COMBOBOX":
                        capt = L[0].split("\"")[1]
                        capt = capt.replace("&","")
                        capt = capt.replace(" ","")
                    else:
                        capt = take_caption(lines, L)
                    if tipe in tipes:
                        idx = tipes.index(tipe)
                        tipe= std_tipes[idx]
                    ides.append("#define ID_{}_{}\t\t\t\t{}".format(tipe, capt, iden))

    new_cnt = ""
    if (os.path.exists(rh)):
        with open(rh, "r") as f:
            cnt = f.read()
            new_cnt = cnt.split("//IDS_INSERTED")[0]
            new_cnt = "{}\n{}\n".format(new_cnt, "//IDS_INSERTED")
            for each in ides:
                new_cnt = "{}\n{}".format(new_cnt, each)
        with open(rh, "w") as f:
            f.write(new_cnt)


if __name__ == "__main__":
    extract()
