FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp2-v0.dir/tp2-v0.cpp.o"
  "tp2-v0.pdb"
  "tp2-v0"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp2-v0.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
