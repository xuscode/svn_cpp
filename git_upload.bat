@echo off
setlocal

:: 获取当前日期和时间
for /f "tokens=2 delims==" %%I in ('wmic OS Get localdatetime /value') do set "dt=%%I"
set "current_date=%dt:~0,4%-%dt:~4,2%-%dt:~6,2%"
set "current_time=%dt:~8,2%:%dt:~10,2%:%dt:~12,2%"

:: 进入脚本所在的目录
cd /d "%~dp0"

:: 初始化Git仓库（如果尚未初始化）
if not exist .git (
    git init
)

:: 添加所有文件到Git仓库
git add .

:: 提交更改，使用当前日期和时间作为日志
git commit -m "Commit at %current_date% %current_time%"

:: 推送到远程服务器
git push origin main

endlocal