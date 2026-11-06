# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

Copy this template to `lab3/README.md` in your own course repository. Follow [the instructions](lab3-instruction.md). Your prediction, debrief and checkpoint answers are already saved by `oslab`; do not copy them here. The marks come from those records and your evidence files; this report is your own record of the lab.

- Student name/ID: SUN SOVISAL, e20230105
- Ubuntu username: gic-sun-sovisal
- My values (`oslab values lab3`): name = silver, tag = backup, v1 = 760, v2 = 770
- Files: `evidence/wildcards.txt`, `evidence/links.txt`, `evidence/replacement.txt`, `evidence/checkpoint.txt`, `evidence/challenge.txt`

## What I Saw

| State | What `cat` printed for the hard link | What `cat` printed for the symbolic link | What `readlink` printed |
|---|---|---|---|
| Before the rename | version 760 | version 760 | silver.txt |
| After the rename, before the repair | version 760 | No such file or directory | silver.txt |
| After a new file took the old name | version 760 | version 770 | silver.txt |
| After my repair | version 760 | version 760 | silver-backup.txt |

My repair (the two commands I wrote):

```bash
rm -- silver-soft.txt
ln -s silver-backup.txt silver-soft.txt
```

## Explanation

`silver-soft.txt` kept storing the path `silver.txt` after the original report was renamed to `silver-backup.txt`. When a new `silver.txt` was created, opening the symbolic link followed that stored name to inode `18752044`, which holds version 770. `silver-hard.txt` and `silver-backup.txt` both still name inode `18743633`, so the hard link still printed version 760. After the repair, `readlink` printed `silver-backup.txt` and the symbolic link printed version 760 again.

## What My Tests Do Not Prove

`cat` shows the bytes reached through a name. Only `ls -li` shows that `silver-hard.txt` and `silver-backup.txt` are the same inode, and that the new `silver.txt` is a different inode.

## Plus / Challenge (only if you did them)

One file had three names, and `ls -l` showed link count 3. After `rm -- one.txt` the remaining names showed link count 2, and `cat two.txt` still printed `keep me`. After `rm -- two.txt` the last name showed link count 1. After `rm -- three.txt` no name remained. The data is gone only when the link count reaches 0.

## AI Note (optional)

An AI tool gave the Core 3 repair commands `rm -- silver-soft.txt` and `ln -s silver-backup.txt silver-soft.txt`. I checked with `cat silver-soft.txt`, which printed version 760, and with `readlink`, which printed `silver-backup.txt`.
