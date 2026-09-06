import os
import subprocess
import sys

ALLOWED_EXTENSIONS = {
    ".cpp": "C++",
    ".cc": "C++",
    ".h": "C++",
    ".hpp": "C++",
    ".py": "Python",
    ".java": "Java",
}

IGNORE_DIRS = {".git", ".github", "build", "__pycache__"}


def escape_latex(text: str) -> str:
    replacements = {
        "\\": r"\textbackslash{}",
        "_": r"\_",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "&": r"\&",
        "{": r"\{",
        "}": r"\}",
        "~": r"\textasciitilde{}",
        "^": r"\textasciicircum{}",
    }
    for char, rep in replacements.items():
        text = text.replace(char, rep)
    return text


def collect_files():
    tree = {}
    for root, dirs, files in os.walk("."):
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS and not d.startswith(".")]
        rel_dir = os.path.relpath(root, ".")
        valid_files = [
            f for f in sorted(files) if os.path.splitext(f)[1] in ALLOWED_EXTENSIONS
        ]
        if valid_files:
            section_name = "General" if rel_dir == "." else rel_dir
            tree[section_name] = [
                os.path.join(root, f).replace("\\", "/") for f in valid_files
            ]
    return tree


def build_latex_document(tree, is_color: bool) -> str:
    color_definitions = (
        r"""
\definecolor{kwcolor}{rgb}{0.0, 0.2, 0.8}
\definecolor{cmtcolor}{rgb}{0.0, 0.5, 0.0}
\definecolor{strcolor}{rgb}{0.7, 0.1, 0.1}
\definecolor{numcolor}{rgb}{0.4, 0.4, 0.4}
\definecolor{framecolor}{rgb}{0.7, 0.7, 0.7}
"""
        if is_color
        else r"""
\definecolor{kwcolor}{rgb}{0.0, 0.0, 0.0}
\definecolor{cmtcolor}{rgb}{0.2, 0.2, 0.2}
\definecolor{strcolor}{rgb}{0.0, 0.0, 0.0}
\definecolor{numcolor}{rgb}{0.3, 0.3, 0.3}
\definecolor{framecolor}{rgb}{0.0, 0.0, 0.0}
"""
    )

    doc = [
        r"\documentclass[9pt,landscape,a4paper]{article}",
        r"\usepackage[left=0.8cm,right=0.8cm,top=1.2cm,bottom=1.2cm]{geometry}",
        r"\usepackage{multicol}",
        r"\usepackage{listings}",
        r"\usepackage{xcolor}",
        r"\usepackage{fancyhdr}",
        r"\usepackage{titlesec}",
        r"\usepackage{tocloft}",
        r"\usepackage{courier}",
        color_definitions,
        r"\lstset{",
        r"  basicstyle=\ttfamily\scriptsize,",
        r"  keywordstyle=\bfseries\color{kwcolor},",
        r"  commentstyle=\itshape\color{cmtcolor},",
        r"  stringstyle=\color{strcolor},",
        r"  numberstyle=\tiny\color{numcolor},",
        r"  numbers=left,",
        r"  stepnumber=1,",
        r"  numbersep=4pt,",
        r"  frame=single,",
        r"  rulecolor=\color{framecolor},",
        r"  tabsize=2,",
        r"  breaklines=true,",
        r"  breakatwhitespace=false,",
        r"  showstringspaces=false,",
        r"  columns=fullflexible,",
        r"  xleftmargin=12pt",
        r"}",
        r"\pagestyle{fancy}",
        r"\fancyhf{}",
        r"\fancyhead[L]{\textbf{Algorithmic Code Library}}",
        (
            r"\fancyhead[C]{\textit{Color Edition}}"
            if is_color
            else r"\fancyhead[C]{\textit{B\&W Edition}}"
        ),
        r"\fancyhead[R]{\thepage}",
        r"\renewcommand{\headrulewidth}{0.4pt}",
        r"\titlespacing*{\section}{0pt}{4pt}{2pt}",
        r"\titlespacing*{\subsection}{0pt}{3pt}{1pt}",
        r"\begin{document}",
        r"\begin{multicols*}{3}",
        r"\tableofcontents",
        r"\vspace{10pt}",
        r"\hrule",
        r"\vspace{10pt}",
    ]

    for section, files in sorted(tree.items()):
        doc.append(f"\\section*{{{escape_latex(section)}}}")
        doc.append(f"\\addcontentsline{{toc}}{{section}}{{{escape_latex(section)}}}")

        for file_path in files:
            file_name = os.path.basename(file_path)
            title = os.path.splitext(file_name)[0]
            ext = os.path.splitext(file_name)[1]
            lang = ALLOWED_EXTENSIONS.get(ext, "C++")

            doc.append(f"\\subsection*{{{escape_latex(title)}}}")
            doc.append(
                f"\\addcontentsline{{toc}}{{subsection}}{{{escape_latex(title)}}}"
            )
            doc.append(f"\\lstinputlisting[language={lang}]{{{file_path}}}")

    doc.append(r"\end{multicols*}")
    doc.append(r"\end{document}")
    return "\n".join(doc)


def compile_latex(tex_name: str):
    # Run twice so table of contents page numbers compute correctly
    for _ in range(2):
        cmd = ["pdflatex", "-interaction=nonstopmode", tex_name]
        res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if res.returncode != 0:
            print(f"Error compiling {tex_name}:")
            print(res.stdout.decode("utf-8", errors="ignore")[-1500:])
            sys.exit(1)


def main():
    tree = collect_files()
    if not tree:
        print("No source code files found to compile.")
        sys.exit(1)

    # 1. Color Edition
    with open("codebook_color.tex", "w", encoding="utf-8") as f:
        f.write(build_latex_document(tree, is_color=True))
    compile_latex("codebook_color.tex")

    # 2. Black & White Edition
    with open("codebook_bw.tex", "w", encoding="utf-8") as f:
        f.write(build_latex_document(tree, is_color=False))
    compile_latex("codebook_bw.tex")

    print("Successfully built codebook_color.pdf and codebook_bw.pdf")


if __name__ == "__main__":
    main()