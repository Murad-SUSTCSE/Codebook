{
  "cmd" : ["g++ -std=c++20 $file_name -o $file_base_name && timeout 5s ./$file_base_name<input.txt>output.txt"],
  "selector" : "source.cpp",
  "shell": true
  //"working_dir" : "$file_path"
}
