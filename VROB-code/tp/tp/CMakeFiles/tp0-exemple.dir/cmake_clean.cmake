FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp0-exemple.dir/tp0-exemple.cpp.o"
  "tp0-exemple.pdb"
  "tp0-exemple"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp0-exemple.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
