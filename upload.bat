set /p commitMessage=Commit message:
git add .
git commit -m "%commitMessage%"
git pull
git push 
pause