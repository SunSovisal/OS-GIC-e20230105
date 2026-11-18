# Lab 4 — Redirection and Pipelines: individual report

Follow the [instruction](lab4-instruction.md). Copy this template into your own `lab4/README.md`. No script is required. Prediction/debrief/checkpoint answers stay in `oslab` records.

- Name / student ID: SUN SOVISAL, e20230105
- Linux account: gic-sun-sovisal
- Personal status and other word: status = `shipped`, other = `sent`

## Commands I Used

Save your actual commands, one per line, in `evidence/commands.txt`. Do not execute that file as a script.

| Stage | My command | Input received | Output produced |
|---|---|---|---|
| Select exact first field | `grep '^shipped,' data/events.csv \| tee evidence/selected.txt` | `data/events.csv` (header + six records) | The three `shipped,` lines (`shipped,4`, `shipped,6`, `shipped,7`), shown and saved to `selected.txt` |
| Extract field 2 | `grep '^shipped,' data/events.csv \| cut -d, -f2 \| tee evidence/fields.txt` | The three selected lines from `grep` through the pipe | The quantities `4`, `6`, `7`, shown and saved to `fields.txt` |
| Count selected records | `grep '^shipped,' data/events.csv \| wc -l > evidence/normal.txt` | The three selected lines from `grep` | `3` in `normal.txt`; `diff -u data/expected.txt evidence/normal.txt` printed nothing |
| Save stdout and stderr separately | `cat data/missing.csv > evidence/stdout.txt 2> evidence/stderr.txt` | A file name that does not exist | Empty `stdout.txt`; `cat: data/missing.csv: No such file or directory` in `stderr.txt` |
| Save exit status immediately | `echo $? > evidence/status.txt` | The exit status of the `cat` command just before it | `1` in `status.txt` |

## What My Tests Show

| Test | Expected | Observed | Mistake it would catch |
|---|---|---|---|
| Original records | 3 exact matches | `3` (`normal.txt`); `diff` against `expected.txt` showed no difference | Using the wrong status word, or a pattern that is too loose or too strict |
| No match | 0 records | `0` (first line of `edge.txt`) | Assuming there is always a match, or matching `sent` rows by mistake |
| One added match plus a look-alike | 4 records | `4` (second line of `edge.txt`) | Leaving out the comma, so `shipped-late` gets counted; adding quantities (7) instead of counting records; using `>` instead of `>>` and losing the first test's result |
| Missing input | empty stdout, diagnostic on stderr, nonzero status | `stdout.txt` empty; `stderr.txt` = `cat: data/missing.csv: No such file or directory`; `status.txt` = `1` | Mixing errors into normal output, or treating a failed read as a successful empty result |

## Explain the Commands

1. **Why does the comma in `grep '^WORD,'` matter?**

   `^` anchors the match to the start of the line and the comma marks the end of the first field. Without the comma, `^shipped` also matches look-alikes such as `shipped-late,31`, and the count would be too high. With it, only records whose first field is exactly `shipped` are selected.

2. **Why does `wc -l` count records here, rather than add quantities?**

   `wc -l` counts newline characters, and each selected record is one line. It never reads what is in field 2, so `shipped,7` counts as 1 record, not 7. The task asks how many records there are, not the total quantity.

3. **Where did you use `>>`, and what would `>` do instead?**

   I used `>>` in `grep '^shipped,' data/changed.csv | wc -l >> evidence/edge.txt` to add the second test result (`4`) under the first (`0`). I also used it to append rows to `data/changed.csv`. With `>`, the file would be emptied first, so `edge.txt` would only contain `4` and the no-match result would be gone.

4. **What does `tee` do that `>` alone does not?**

   `tee` writes its input to a file **and** to stdout at the same time, so I can see the result on screen (or send it on down the pipe) while also saving it. `>` sends stdout only to the file, so nothing appears on the terminal. `tee -a` appends instead of replacing.

5. **Why must `echo $?` immediately follow the command being checked?**

   `$?` holds the exit status of the most recent command only. If another command runs in between (even `cat evidence/stdout.txt`), `$?` changes to that command's status, and I would save the wrong value (often `0`).

6. **Why can `cat missing-file | wc -l` report pipeline status 0?**

   A pipeline's status is normally the status of its **last** command. `cat` fails with status 1 and prints a diagnostic on stderr, which does not go into the pipe. `wc -l` still gets valid, empty input, prints `0` and exits successfully, so the whole pipeline reports 0. A successful last stage does not prove that the input was read.

## Limits and Evidence

These commands assume simple comma-separated text without quoted commas. Saved results describe one run; they do not prove every future input works or who typed a command.

Check the submission tree in the instruction: include `checkpoint.txt` and all required evidence files, including the empty `stdout.txt`. No `report.sh` is required.

Live checkpoint: the selected rows from the fresh file (`shipped,7`, `shipped,16`) are saved in `evidence/checkpoint-selected.txt`, and the record count `2` is saved in `checkpoint.txt`.

## Optional Work / AI Note

- **Guided practice:** `evidence/tee-demo.txt` shows `tee` replacing the file and then `tee -a` appending a second line. `evidence/demo-error.txt` and the empty `evidence/demo-out.txt` show stderr kept apart from stdout. `evidence/both.txt` shows both streams sent to one file (`events.csv` contents followed by the missing-file diagnostic).
- **Plus / Challenge:** Completed.
- **AI note:** I used AI to help write up this report from my saved evidence. My predictions and checkpoint answers were done without AI.
