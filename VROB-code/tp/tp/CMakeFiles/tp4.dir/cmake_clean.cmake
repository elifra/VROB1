FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp4.dir/tp4.cpp.o"
  "tp4.pdb"
  "tp4"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp4.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
