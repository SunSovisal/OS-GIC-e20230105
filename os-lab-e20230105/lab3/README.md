# Lab 3 — Wildcards and Links: individual report

Copy this template to `lab3/README.md` in your own course repository. Follow [the instructions](lab3-instruction.md).

- Student name/ID: SUN SOVISAL, e20230105
- Ubuntu username and environment: gic-sun-sovisal on shared Ubuntu server (i4gic-os)
- Artifact paths: [evidence/links.txt](evidence/links.txt), [evidence/replacement.txt](evidence/replacement.txt)

## Original Prediction

Captured on the course worksheet / paper before the rename experiment.

After `source.txt` becomes `renamed.txt`, a hard link will still read the old bytes. A hard link is another directory name for the same inode. Whereas a symbolic link storing `source.txt` will break. A symbolic link stores a path string, not an inode.

## Test Evidence

- [evidence/links.txt](evidence/links.txt) — before rename, dangling soft link after rename, and repair
- [evidence/replacement.txt](evidence/replacement.txt) — new `source.txt` vs hard link

| Test | Claim | Result that would contradict it | Observed result | What remains unproven |
|---|---|---|---|---|
| two link types before rename | `hard.txt` shares inode with `source.txt`; `soft.txt` stores path `source.txt` and both read the same content | Different inodes for hard and source, or soft already broken | Inode `18743633` for `source.txt` and `hard.txt`; soft inode `18743724` with target `source.txt` ([links.txt](evidence/links.txt)) | That the soft link would survive a rename |
| dangling link and recreated filename | Soft link fails after rename, works after retarget to `renamed.txt`; new `source.txt` is version 2 while hard keeps version 1 | Soft still works after rename, or hard becomes version 2 | After rename: `cat soft.txt` → No such file or directory; after repair soft → `renamed.txt` and both show version 1. New `source.txt` inode `18743740` = version 2; hard inode `18743633` = version 1 ([links.txt](evidence/links.txt), [replacement.txt](evidence/replacement.txt)) | Soft-link behavior with absolute targets or across filesystems |

## Explanation and Correction

**Confirmed.** The prediction matches the evidence in [links.txt](evidence/links.txt) and [replacement.txt](evidence/replacement.txt).

`hard.txt` and `renamed.txt` share inode `18743633` (link count 2), so they are two names for the same file data. `soft.txt` has its own inode and stores a path (`source.txt`, later repaired to `renamed.txt`).

(a) Renaming `source.txt` to `renamed.txt` broke the symbolic link.
(b) Hard link survived because it points at the inode, not the name.
(c) Creating a new `source.txt` with different bytes creates a new inode. `hard.txt` still names the old inode, so it keeps the old content.

## Cleanup

No owned processes, jobs, or mounts were created. Only files under `~/oslab-work/lab3` were used. The supervised changed-case checkpoint was collected separately and is not reconstructed here.
