name=backup/`date +"%Y%m%d_%H%M"`
echo $name
mkdir $name
mv log $name
mv ckpt $name
