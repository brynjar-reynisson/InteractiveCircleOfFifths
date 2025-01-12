import glob

def create_resource(file_list, root_dir):
  resource = ""
  for filename in file_list:
    idx = filename.rfind('\\')
    short_name = filename[idx+4:]
    short_name = short_name[:-4]
    resource += short_name
    resource += "\n"
    with open(filename, 'r') as file:
      file_content = file.read()
      resource += file_content
      resource += "\n"
  return resource
    
lm_file_list = []
lm_root_dir='C:\\Users\\Lenovo\\Downloads\\Light_mode\\'
for filename in glob.iglob(lm_root_dir + '**\\*.svg', recursive=True):
  lm_file_list.append(filename)
     
dm_file_list = []
dm_root_dir='C:\\Users\\Lenovo\\Downloads\\Dark_Mode\\'
for filename in glob.iglob(dm_root_dir + '**\\*.svg', recursive=True):
  dm_file_list.append(filename)

lm_resource = create_resource(lm_file_list, lm_root_dir)
dm_resource = create_resource(dm_file_list, dm_root_dir)

with open("Light_mode.txt", "w") as f:
    f.write(lm_resource)
    
with open("Dark_mode.txt", "w") as f:
    f.write(dm_resource)