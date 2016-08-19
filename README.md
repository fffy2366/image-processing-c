
```python
import subprocess
subprocess.call(["dir"],shell=True,cwd="D:/c")
subprocess.call(["image-processing.exe","f2a75fb0-5e87-11e6-b75e-87fc586a8584.png"],shell=True,cwd="D:/c/image-processing/x64/Debug")


p = subprocess.Popen(["image-processing.exe","4","D:\\photo\\api\\","bcbda8e0-5eb0-11e6-b75e-87fc586a8584.png"],shell=True,cwd="D:/c/image-processing/x64/Debug",stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
stdoutput,erroutput = p.communicate(input=None)
print stdoutput


#p.wait()

```




## jsoncpp
https://github.com/open-source-parsers/jsoncpp
http://jsoncpp.sourceforge.net/old.html