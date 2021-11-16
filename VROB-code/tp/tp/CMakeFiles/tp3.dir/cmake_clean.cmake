FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp3.dir/tp3.cpp.o"
  "tp3.pdb"
  "tp3"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp3.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
