# Lab 2 — Linux Navigation and File Management: individual report

Copy this template to `lab2/README.md` in your own course repository. Follow [the instructions](lab2-instruction.md). Your prediction, debrief and checkpoint answers are already saved by `oslab`; do not copy them here. The marks come from those records and your evidence files; this report is your own record of the lab.

- Student name/ID: SUN SOVISAL, e20230105
- Ubuntu username: gic-sun-sovisal
- My values (`oslab values lab2`): file1 = payroll may.txt, file2 = tax summary.txt, owner = Audit, reader = Engineering, third = Support
- Files: `evidence/paths.txt`, `evidence/tree.txt`, `evidence/checkpoint.txt`

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | `mv -- "payroll may.txt" ../reports/` | `/home/gic-sun-sovisal/oslab-work/lab2/incoming` |
| Move the second file (absolute paths) | `mv -- "/home/gic-sun-sovisal/oslab-work/lab2/incoming/tax summary.txt" "/home/gic-sun-sovisal/oslab-work/lab2/reports/"` | `/home/gic-sun-sovisal/oslab-work/lab2` |
| Read the report from my reader department (relative path) | `cat "../Audit/payroll may.txt"` | `/home/gic-sun-sovisal/oslab-work/lab2/TechCorp/Engineering` |
| The path error I made on purpose, and its message | `cat "reports/payroll may.txt"` gave `cat: 'reports/payroll may.txt': No such file or directory` | `/home/gic-sun-sovisal/oslab-work/lab2/TechCorp/Engineering` |
| The relative path that fixed it | `../../reports/payroll may.txt` | `/home/gic-sun-sovisal/oslab-work/lab2/TechCorp/Engineering` |

## Explanation

A correct file name can still give "No such file or directory" when the path starts from the wrong folder. From `TechCorp/Engineering`, `reports/payroll may.txt` looks for `TechCorp/Engineering/reports/payroll may.txt`, and that folder was never created. The same file is reached with `../../reports/payroll may.txt`, because `../..` is the lab folder. `mv` took `payroll may.txt` out of `incoming/` and left it only in `reports/`. `cp` then made a second `payroll may.txt` in `TechCorp/Audit/` and left the original in `reports/`.

## What My Tests Do Not Prove

`ls` and `tree.txt` show the file names. They do not show that the copies have the same bytes. `cmp` shows the bytes match, and it does not show that a relative path will work after I change directory.

## Plus / Challenge (only if you did them)

I did not do Plus or Challenge.

## AI Note (optional)

An AI tool helped me create a folder named `SUBMISSION_REPO` in my home directory. I checked with `tree`: that folder is not my course repo. The lab files belong in `/home/gic-sun-sovisal/os-gic-e20230105/os-lab-e20230105`.
