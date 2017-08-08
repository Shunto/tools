import os
import zipfile
import requests

torURL = "https://dist.torproject.org/torbrowser/4.5.3/tor-win32-0.2.6.9.zip"
torSHA256 = "8d2eda25e32328962c77a829f030a326226fb6c82e658b8cc38b6cfd8d996320"

def downloadTor(outputFoloder):
    while True:
        doBreak = False
        try:
            data = urlopen(torURL).read()
            req = Request(torURL)
            req.add_unredirected_header("User-Agent", "Mozilla/5.0")
            data = urlopen(req).read()
            del(req)
            with open(outputFolder+"tor.zip", "wb") as code:
                code.write(data)
            with open(outputFolder+"tor.zip", "r") as code:
                if gethash(code.read()) == torSHA256:
                    sourceZip = ZipFile(outputFolder+"tor.zip", "r")
                    for name in sourceZip.namelist():
                        sourceZip.extractcall(outputFoler, name)
                    sourceZip.close()
                    doBreak = True
            remove(outputFolder+"tor.zip")
        except:
            pass
        if doBreak == True:
            break
        else:
            if os.path.isfile(outputFolder+"tor.zip"):
                try:
                    remove(outputFolder+"tor.zip")
                except:
                    pass

if __name__ == "__main__":
    #ouputFolder = raw_input("Designate the output folder:")
    #os.mkdir("./output")
    outputFolder = "output"
    downloadTor(outputFolder)
