# ESP32_EC

ESP32 EC（Embedded Controller）開發專案。

---

# GitHub Repository

## 建立 GitHub Repository

1. 登入 GitHub，點擊右上角 **`+` → `New repository`**。
2. 輸入 `Repository name`，例如：

   ```text
   ESP32_EC
   ```
3. 不要勾選：

   * `Add a README file`
   * `.gitignore`
   * `Choose a license`
4. 點擊 **Create repository**。
5. 複製 GitHub 顯示的 HTTPS Repository URL。

例如：

```text
https://github.com/hongyi2919/ESP32_EC.git
```

> 建議建立空的 Repository，避免本地與遠端 Repository 的 Commit History 不一致。

---

# 本地端 Git 設定

進入專案資料夾：

```bash
cd 專案名稱
```

或直接在專案資料夾中點選：

```text
Open Git Bash here
```

## 1. 初始化 Git Repository

```bash
git init
```

## 2. 建立 README.md

```bash
echo "# ESP32_EC" >> README.md
```

## 3. 加入所有檔案

```bash
git add .
```

## 4. 查看目前狀態

```bash
git status
```

確認需要的檔案已加入 Staging Area。

## 5. 建立第一個 Commit

```bash
git commit -m "initial commit"
```

## 6. 設定 GitHub Remote

```bash
git remote add origin https://github.com/hongyi2919/ESP32_EC.git
```

## 7. 確認 Remote 設定

```bash
git remote -v
```

應該會看到：

```text
origin  https://github.com/hongyi2919/ESP32_EC.git (fetch)
origin  https://github.com/hongyi2919/ESP32_EC.git (push)
```

## 8. Push 到 GitHub

```bash
git push
```

---

# Branch

GitHub 預設主要 Branch 為 `main`，因此建議將本地 `master` 改成 `main`。

## 將 Branch 改成 main

```bash
git branch -M main
```

## 第一次 Push main

```bash
git push -u origin main
```

之後可以直接使用：

```bash
git push
```

---

# Commit

## 一般 Commit

修改程式碼後：

```bash
git add .
git commit -m "新增功能或修正"
git push
```

如果要指定 Branch：

```bash
git push origin feature
```

---

## 修改最近一次自己的 Commit

如果要將新的修改加入最近一次 Commit：

### 1. 加入 Staging Area

```bash
git add .
```

### 2. 修改最近一次 Commit

```bash
git commit --amend
```

如果不想修改原本的 Commit Message：

```bash
git commit --amend --no-edit
```

### 3. 強制 Push 到遠端

如果原本的 Commit 已經 Push 到 GitHub：

```bash
git push --force origin main
```

如果是其他 Branch：

```bash
git push --force origin 分支名稱
```

> ⚠️ `git push --force` 會改寫遠端 Commit History。
> 使用前請確認該 Commit 是自己的，避免影響其他人的修改。

---

# 刪除 Commit

## 刪除本地最後一次 Commit

```bash
git reset --hard HEAD^
```

這會將本地 Repository 回復到上一個 Commit。

> ⚠️ `--hard` 會同時捨棄尚未 Commit 的修改，使用前請確認沒有需要保留的程式碼。

## 已經 Push 到 GitHub

如果 Commit 已經推送到遠端：

```bash
git reset --hard HEAD^
git push --force
```

執行後，GitHub 遠端 Branch 也會回到上一個 Commit。

> ⚠️ 此操作會改寫遠端 Commit History，請謹慎使用。

---

# Feature Branch

開發新功能時，可以建立 Feature Branch，避免直接修改 `main`。

## 建立並切換 Feature Branch

```bash
git checkout -b feature
```

## 開發完成後 Commit

```bash
git add .
git commit -m "新增功能或修正"
```

## Push Feature Branch

```bash
git push origin feature
```

---

# 合併分支

假設要將 `feature` 合併到 `main`。

## 1. 切換到 main

```bash
git checkout main
```

## 2. 合併 feature

```bash
git merge feature
```

## 3. 如果沒有衝突

直接 Push：

```bash
git push origin main
```

---

# Merge Conflict

如果 Merge 時遇到衝突，例如：

```text
fatal: You are in the middle of a merge -- cannot amend
```

代表目前仍處於 **Merge 進行中**，不能直接使用 `git commit --amend`。

## 解決方式

### 1. 查看衝突狀態

```bash
git status
```

### 2. 手動解決衝突

打開 Git 顯示有 Conflict 的檔案，處理：

```text
<<<<<<< HEAD
main 的內容
=======
feature 的內容
>>>>>>> feature
```

保留需要的內容後，移除：

```text
<<<<<<< HEAD
=======
>>>>>>>
```

### 3. 將解決後的檔案加入 Staging Area

```bash
git add .
```

### 4. 完成 Merge Commit

```bash
git commit
```

Git 會自動產生 Merge Commit Message，也可以自行修改。

### 5. Push 到 GitHub

```bash
git push origin main
```

完整流程：

```bash
git checkout main
git merge feature

# 如果發生 Conflict
git status

# 手動解決 Conflict
git add .
git commit

# Push
git push origin main
```

> ⚠️ Merge Conflict 尚未解決時，不要使用 `git commit --amend`。
> 應先解決 Conflict → `git add .` → `git commit` 完成 Merge。

---

# 查看 Branch

查看目前有哪些 Branch：

```bash
git branch
```

例如：

```text
* main
  feature
  function_B
```

`*` 代表目前所在的 Branch。

---

# 清理多餘 Branch

當 Feature Branch 已經完成 Merge 且不再使用，可以刪除。

## 刪除本地 Branch

```bash
git branch -D function_B
```

或：

```bash
git branch -D feature
```

## 刪除 GitHub 遠端 Branch

```bash
git push origin --delete function_B
```

或：

```bash
git push origin --delete feature
```

> `git branch -D` 是強制刪除 Branch，使用前請確認 Branch 中沒有需要保留的 Commit。

---

# 查看目前修改

```bash
git status
```

可以查看：

* 目前所在的 Branch
* 哪些檔案被修改
* 哪些檔案尚未加入 Staging Area
* 哪些檔案已加入 Staging Area
* 是否有尚未 Commit 的修改
* 是否正在進行 Merge

---

# 查看 Git Branch 圖

使用以下指令查看完整的 Commit 與 Branch 關係：

```bash
git log --oneline --graph --decorate --all
```

例如：

```text
*   8a12c3d (HEAD -> main) Merge branch 'feature'
|\
| * 4b56ef7 (feature) add power sequence
| * 91ac123 update GPIO
|/
* 72cd456 initial commit
```

## 常用參數

| 參數           | 說明                     |
| ------------ | ---------------------- |
| `--oneline`  | 每個 Commit 顯示成一行        |
| `--graph`    | 以 ASCII 圖形顯示 Branch 關係 |
| `--decorate` | 顯示 Branch、Tag 等資訊      |
| `--all`      | 顯示所有 Branch            |

---

# 常用 Git 指令

| 功能                     | 指令                                           |
| ---------------------- | -------------------------------------------- |
| 初始化 Git                | `git init`                                   |
| 查看目前修改                 | `git status`                                 |
| 加入所有檔案                 | `git add .`                                  |
| 建立 Commit              | `git commit -m "message"`                    |
| 修改最近一次 Commit          | `git commit --amend`                         |
| 修改 Commit 且保留原 Message | `git commit --amend --no-edit`               |
| 查看 Branch              | `git branch`                                 |
| 查看 Remote              | `git remote -v`                              |
| 新增 Remote              | `git remote add origin <URL>`                |
| Push                   | `git push`                                   |
| Push 指定 Branch         | `git push origin <branch>`                   |
| 強制 Push                | `git push --force origin <branch>`           |
| 建立並切換 Branch           | `git checkout -b <branch>`                   |
| 切換 Branch              | `git checkout <branch>`                      |
| 合併 Branch              | `git merge <branch>`                         |
| 刪除本地 Branch            | `git branch -D <branch>`                     |
| 刪除遠端 Branch            | `git push origin --delete <branch>`          |
| 刪除最後一次 Commit          | `git reset --hard HEAD^`                     |
| 查看 Branch 圖            | `git log --oneline --graph --decorate --all` |

---

# 常見開發流程

## 一般開發

```bash
git status
git add .
git commit -m "新增功能或修正"
git push
```

## Feature Branch 開發

```bash
# 建立並切換 Feature Branch
git checkout -b feature

# 修改程式碼
git status

# Commit
git add .
git commit -m "新增功能或修正"

# Push Feature Branch
git push origin feature

# 切換回 main
git checkout main

# 合併 feature
git merge feature

# 如果沒有 Conflict
git push origin main

# 如果有 Conflict
# 1. 手動解決 Conflict
# 2. git add .
# 3. git commit
# 4. git push origin main

# Feature 完成後清理 Branch
git branch -D feature
git push origin --delete feature
```
