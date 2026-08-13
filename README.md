ESP32_EC
將專案上傳到git 步驟

1.登入 GitHub，點擊右上角的 + 號選擇 New repository。

2.輸入 Repository name（例如：embedded-control-test）。

3.不要勾選 "Add a README file"、".gitignore" 或 "Choose a license"（保持空的 Repository，才能避免本地與遠端版本歷史不一致）。

4.點擊 Create repository，並複製頁面顯示的 HTTPS 網址

本地端
cd 專案名稱 (或是專案資料夾 Opem Git Bash here)
1.git init
2.echo "# 專案名稱" >> README.md   # 建立 README
3.git add .                        # 加入所有檔案
4.git status                       # 確認檔案已 staged
5.git commit -m "initial commit"   # 本地建立commit
6.git remote add origin https://github.com/hongyi2919/ESP32_EC.git  #剛剛Create repository網址
7.git remote -v                    # 確認遠端設定
(應該會看到
origin  https://github.com/hongyi2919/ESP32_EC.git (fetch)
origin  https://github.com/hongyi2919/ESP32_EC.git (push)
)


設定 branch 並推送
GitHub 預設 branch 是 main，所以建議把本地 master 改成 main
1.git branch -M main
2.git push -u origin main

當要修改某次自己的commit
git add .            # 把要補進去的檔案放到 staging area
git commit --amend   # 修改最近一次 commit，把 staged 檔案加進去
git push --force     # 強制覆蓋遠端的舊 commit

