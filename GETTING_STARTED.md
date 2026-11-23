# Getting started with AE4080 Phase 3 on Windows

Use VS Code to edit the project and run commands. The build script uses the C++ compiler from Visual Studio 2026 or its Build Tools installation.

## 1. Check what you have installed

- **Visual Studio 2026 or Build Tools 2026.** If you already have it for PESST-FD, open **Visual Studio Installer** from the Start menu, find the 2026 installation, and select **Modify**. Under **Workloads**, check **Desktop development with C++**. Confirm that the x64/x86 MSVC tools and a Windows SDK are selected. [Visual Studio C++ components](https://learn.microsoft.com/en-us/visualstudio/install/workload-component-id-vs-community?view=vs-2026#desktop-development-with-c)
- **VS Code.** Install the Windows version and open it from the Start menu. Open **Extensions** in the left sidebar and install **C/C++** by Microsoft for code completion and navigation. [VS Code for Windows](https://code.visualstudio.com/docs/setup/windows)
- **Git for Windows.** Install Git and keep **Git Credential Manager** selected if the installer offers it. Close and reopen VS Code after installing Git so it can pick up the new command. [Git for Windows](https://git-scm.com/install/windows) · [GitHub sign-in with Git Credential Manager](https://docs.github.com/en/get-started/git-basics/caching-your-github-credentials-in-git)

## 2. Clone the project and open it

The repository is public, so you can clone it and run it before creating a GitHub account.

1. In VS Code, select **File > Open Folder** and pick a folder where you want to store the project. This will be the parent folder for the clone.
2. Select **Terminal > New Terminal**. A panel opens at the bottom of VS Code. If it opens a different shell, use the dropdown next to the **+** in the terminal panel and choose **PowerShell**. Type each command in this panel and press **Enter**. [VS Code terminal basics](https://code.visualstudio.com/docs/terminal/getting-started)
3. Check that Git is available and clone the repo. Cloning creates an `AEROTHERMO-Phase-3` folder in the current location.

   ```powershell
   git --version
   git clone https://github.com/V4VAA/AEROTHERMO-Phase-3.git
   ```

4. Select **File > Open Folder** again and open the new **AEROTHERMO-Phase-3** folder. The Explorer sidebar should show `src`, `EquilFlow`, and `run.cmd`. Open **Terminal > New Terminal** in this folder.

## 3. Build and run

In the VS Code terminal, run:

```powershell
.\run.cmd
```

The script finds the Visual Studio 2026 compiler, builds an optimized x64 executable at `build\AE4080.exe`, and starts it. The current driver prints the Mach 35, 22, and 10.5 cases and writes `aero_results.csv` in the project folder. Run the same command after editing any C++ source.

- If `git` is unrecognized, restart VS Code and try `git --version` again. If it still fails, check the Git for Windows installation.
- If `run.cmd` is unrecognized, run `Get-Location` and `Get-ChildItem`. The location should be the **AEROTHERMO-Phase-3** folder, and `run.cmd` should appear in the list.
- If the script reports that the x64 C++ build tools are missing, go back to **Visual Studio Installer > Modify** and check the 2026 C++ workload.

## 4. Set up GitHub when you are ready to share

1. Create a free GitHub account and verify your email. [GitHub sign-up instructions](https://docs.github.com/en/account-and-profile/how-tos/account-management/creating-an-account-on-github)
2. Send your GitHub username to the repo owner and accept their collaborator invitation. That gives you permission to push a branch to the shared project. [GitHub collaborator access](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/repository-access-and-collaboration/inviting-collaborators-to-a-personal-repository)
3. In the repo terminal, set the name and email Git should put on your commits. Replace the example values with your own. You can use your GitHub-provided `noreply` address if you want to keep your email private. [GitHub commit email settings](https://docs.github.com/en/account-and-profile/how-tos/email-preferences/setting-your-commit-email-address)

   ```powershell
   git config user.name "Your Name"
   git config user.email "your-email@example.com"
   ```

## 5. Share your first change

Start from the latest `main` and create a branch for your work. `heating-baseline` is an example branch name.

```powershell
git switch main
git pull --ff-only
git switch -c heating-baseline
```

Edit your files in VS Code, save them with **Ctrl+S**, then run `.\run.cmd` to check your changes. Use `git status` to see the changed files. The commands below show how to save and upload changes to the heating files. Substitute the files you actually edited.

```powershell
git status
git add -- src/heating.cpp src/heating.h
git commit -m "Add baseline heating calculation"
git push -u origin heating-baseline
```

If a browser sign-in opens on the first push, sign in with the GitHub account that accepted the invitation. Then open the repo on GitHub, select **Compare & pull request** for your branch, and use `main` as the base. A pull request lets the team review your changes before merging. [Project repository](https://github.com/V4VAA/AEROTHERMO-Phase-3)
