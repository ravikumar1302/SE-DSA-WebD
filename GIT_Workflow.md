# 🚀 Git Workflow & Most Used Commands

This project follows a **Pull Request based workflow**

✅ Always create and work on feature branches  
✅ Raise PR  
✅ Manager reviews & merges  
❌ Never push directly to `develop` and `main` branch

---

## 🧠 Branch Strategy

| Branch                                | Purpose                                              |
| ------------------------------------- | ---------------------------------------------------- |
| `main`                                | Production code                                      |
| `develop`                             | Main protected branch and active development branch  |
| `feature branches`                    | Developers working area                              |
| `feature/developer-name/feature-name` | new feature added, like `feature/ravi/about-us-page` |
| `fix/developer-name/feature-name`     | bug fix like `fix/ravi/instagram-icon-color`         |

---

## 🌿 Branch Naming Convention

```
developer-name/feature-name
```

Examples:

```
ravi/navbar
ravi/auth-system
shubham/dashboard-ui
```

---

<br> <br>

# 🔥 Standard Developer Workflow

```
git checkout develop                         # switch to development branch
git pull origin develop                      # get latest code from main/develop branch
git checkout -b yourname/feature-name        # Create new branch AND switch to it
# Do coding
git add .
git commit -m "Describe your change"
git push origin yourname/feature-name       # Upload your new branch to GitHub (or You tell Git: Publish my work online)
```

After push:

- Open GitHub and Click **Compare & Create Pull Request**
- Manager will review change → Merge into `develop` or `main`

---

# Regular Git Sync

1. STEP 1 — Save Your Current Work (Backup Your Feature)

    ```
    git checkout feature/<name>
    git add .
    git commit -m "WIP"
    git push
    ```

2. STEP 2 — Update Local Develop Branch

    ```
    git checkout develop
    git pull origin develop
    ```

3. STEP 3 — Bring Latest Team Changes Into Your Feature

    ```
    git checkout feature/<name>
    git merge develop
    ```

4. STEP 4 — Fix Conflicts (If Any), then run

    ```
    git add .
    git commit
    ```

5. Push Updated Feature Branch

    ```
    git push
    ```

---

<br> <br>

# 📦 Essential Git Commands (Quick Reference)

| Command                                                                                                  | What it Does                                                  |
| -------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| `git checkout develop`                                                                                   | Switch to main branch                                         |
| `git pull origin develop`                                                                                | Download latest code from GitHub                              |
| `git checkout -b name/feature`                                                                           | Create new branch + switch to it                              |
| `git branch`                                                                                             | Show current branch                                           |
| `git branch -a`                                                                                          | Show all local & remote branches                              |
| `git status`                                                                                             | Show changed files                                            |
| `git add .`                                                                                              | Stage all changes                                             |
| `git add filename`                                                                                       | Stage specific file                                           |
| `git commit -m "message"`                                                                                | Save changes locally                                          |
| `git push origin branch-name`                                                                            | Upload branch to GitHub                                       |
| `git fetch origin`                                                                                       | Fetch latest remote branches without modifying code           |
| `git pull origin develop --rebase`                                                                       | Download remote updates without modifying local files         |
| `git checkout develop`<br>`git pull origin develop`<br>`git checkout branch-name`<br>`git merge develop` | Update feature branch with latest main code (avoid conflicts) |
| `git log --oneline`                                                                                      | View commit history                                           |
| `git restore .`                                                                                          | Discard uncommitted changes                                   |
| `git stash`                                                                                              | Temporarily save uncommitted work                             |
| `git stash pop `                                                                                         | Restore stashed work                                          |
| `git reset --soft HEAD~1`                                                                                | Undo last commit (keep changes)                               |
| `git branch -d branch-name`                                                                              | Delete local branch                                           |
| `git push origin --delete branch-name`                                                                   | Delete branch on GitHub                                       |

---

## ⭐ Team Rules

- Always pull latest `develop` before coding or raising a PR
- One feature = One branch
- Use meaningful commit messages
- PR required for all changes
- Do NOT push directly to `develop`

---

## ✅ Pull Request Checklist

Before creating PR:

- [ ] Code builds successfully
- [ ] Latest `develop` merged
- [ ] No console errors
- [ ] Proper commit message written
- [ ] Tested locally
- [ ] No unnecessary console.log / debug code

---

## 🎯 Goal

Clean history • Easy collaboration • Zero merge chaos 🚀

---

<br> <br><br>

# Merge vs Rebase

Both are used to update your feature branch with latest main code

- Merge = Safe
- Rebase = Clean history

---

## ✅ Merge (Safe Method — Recommended for Beginners)

```
git checkout develop
git pull origin develop
git checkout branch-name
git merge develop
```

### Result

- Keeps full history
- Creates a merge commit
- Safe for teams

Example history:

```
A --- B --- C (develop)
       \
        D --- E (feature)
                 \
                  M (merge commit)
```

---

## 🚀 Rebase (Clean Method — Advanced)

```
git checkout branch-name
git pull origin develop --rebase
```

### Result

- Cleaner commit history
- No merge commits
- Looks linear

Example history:

```
A --- B --- C --- D --- E
```

---

## ⭐ Key Difference

| Merge                 | Rebase                      |
| --------------------- | --------------------------- |
| Safe                  | Cleaner                     |
| Keeps branch history  | Rewrites history            |
| Easier for juniors    | Better for experienced devs |
| Creates merge commits | No merge commits            |

---

## ⚠️ Team Rule

✅ Rebase your **own feature branch**  
❌ Never rebase shared branches (`develop`)
