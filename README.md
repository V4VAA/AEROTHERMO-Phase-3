# AE4080 Phase 3

## Build and run

Install **Visual Studio 2026** or **Build Tools for Visual Studio 2026** with
the **Desktop development with C++** workload, including the x64 MSVC tools
and a Windows SDK.

Open PowerShell in the repository root and run the project:

```powershell
.\run.cmd
```

Edit the `cases` vector in `src/main.cpp` to set the inputs. Each row has
these eight values:

```text
type h0 V0 gamma0 AoA m Sref rnose
```

Use type 1 for the ellipsoid or type 2 for the biparabolic body. Use metres,
metres per second, radians for both angles, kilograms, square metres, and
metres for the nose radius, respectively.

The command builds an optimized x64 executable and writes `trajectory.csv`
and `results.csv`. The latter reports peak stagnation-point convective heat
flux, time of peak, and integrated heat load for each case.

To rerun an existing build from the repository root, use
`.\build\AE4080.exe`. EquilFlow reads its gas and species data relative to that
directory.
