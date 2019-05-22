cd build/plugins
for d in *; do
  if [ -d "$d" ] && [ $(basename $d) != "CMakeFiles" ]; then
    cd $d
    echo "$PWD:"
    python3 setup.py install --user 
    cd ..
  fi
done
cd ..
python3 setup.py install --user 
