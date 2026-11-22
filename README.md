# AE4080 Phase 3

## Build and run

Install **Visual Studio 2026** or **Build Tools for Visual Studio 2026** with
the **Desktop development with C++** workload, including the x64 MSVC tools
and a Windows SDK.

Open PowerShell in the repository root and run the project:

```powershell
.\run.cmd
```

The command builds an optimized x64 executable at `build\AE4080.exe` and runs
the Mach 35, 22, and 10.5 flight cases. Shock and transport results print to
the console. Each run writes `aero_results.csv` in the repository root.

To rerun an existing build from the repository root, use
`.\build\AE4080.exe`. EquilFlow reads its gas and species data relative to that
directory.
