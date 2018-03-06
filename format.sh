#!/bin/bash

# find ./include \( -name "*.h" -or -name "*.c" \) ! -path "./include/*/sqlite3.h" -print0 | xargs -0 clang-format -i
# find ./src \( -name "*.h" -or -name "*.c" \) ! -path "./src/*/sqlite3.c" -print0 | xargs -0 clang-format -i
# find ./tests \( -name "*.h" -or -name "*.c" \) -print0 | xargs -0 clang-format -i
# astyle --recursive "./include/*.h" "./src/*.c" "./tests/*.c" "./tests/*.h" \
# -n --indent-namespaces --max-code-length=80 --min-conditional-indent=0 \
# --pad-oper --align-pointer=name

clang-format -i ./src/main.c
astyle "./src/main.c" \
-n --indent-namespaces --max-code-length=80 --min-conditional-indent=0 \
--pad-oper --align-pointer=name

find ./tests \( -name "*.h" -or -name "*.c" \) -print0 | xargs -0 clang-format -i
astyle --recursive "./tests/*.c" "./tests/*.h" \
-n --indent-namespaces --max-code-length=80 --min-conditional-indent=0 \
--pad-oper --align-pointer=name

find ./include/utils \( -name "*.h" -or -name "*.c" \) -print0 | xargs -0 clang-format -i
find ./src/utils \( -name "*.h" -or -name "*.c" \) -print0 | xargs -0 clang-format -i
astyle --recursive "./include/utils/*.h" "./src/utils/*.c" \
-n --indent-namespaces --max-code-length=80 --min-conditional-indent=0 \
--pad-oper --align-pointer=name

find ./include/crypto \( -name "*.h" -or -name "*.c" \) -print0 | xargs -0 clang-format -i
find ./src/crypto \( -name "*.h" -or -name "*.c" \) -print0 | xargs -0 clang-format -i
astyle --recursive "./include/crypto/*.h" "./src/crypto/*.c" \
-n --indent-namespaces --max-code-length=80 --min-conditional-indent=0 \
--pad-oper --align-pointer=name
