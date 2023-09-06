#!/bin/sh -e

cat << EOM > functions.md
# Libxtend function list

Each function below is documented by a man page.  To view the documentation,
install libxtend using your chosen package manager and run \`man function\`
(e.g. \`man dsv_read_field\`).

| Function | Purpose |
|----------|---------|
EOM

auto-man2man Man/* | awk -F - '$1 !~ "libxtend" { printf("| %s | %s |\n", $1, $2); }' \
    >> functions.md

grip --export functions.md
firefox ./functions.html
