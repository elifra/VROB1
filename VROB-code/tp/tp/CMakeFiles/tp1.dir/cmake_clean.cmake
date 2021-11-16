FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp1.dir/tp1.cpp.o"
  "tp1.pdb"
  "tp1"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp1.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
