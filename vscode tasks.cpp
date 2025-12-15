{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "CP Build & Run",
      "type": "process",
      "command": "bash",
      "args": [
        "-c",
        "ulimit -s262144 -f102400 -t5 && g++ -O2 -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer \"${file}\" -o /tmp/a.out && /usr/bin/time -f \"%esec | %MKB\" /tmp/a.out < in.txt > out.txt"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": {
        "owner": "cpbuild",
        "fileLocation": "absolute",
        "pattern": [
          {
            "regexp": "^(.*):([0-9]+):([0-9]+):\\s+(fatal error|error|warning):\\s+(.*)$",
            "file": 1,
            "line": 2,
            "column": 3,
            "severity": 4,
            "message": 5
          }
        ]
      },
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "presentation": {
        "clear": true,
        "revealProblems": "onProblem",
        "showReuseMessage": false
      }
    }
  ]
}
