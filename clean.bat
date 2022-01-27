del /s code*.exe
del /s tempCodeRunnerFile.*
FOR /d /r . %%d IN (build) DO @IF EXIST "%%d" rd /s /q "%%d"