protoc -I=./proto --cpp_out=./protocpp ./proto/*.proto
%xcopy  .\protocpp\*.* ..\Project1\protoc\ /S /C /Y%
pause