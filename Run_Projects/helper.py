import shutil
import os

targets = ['asa_1819_p2']


def remove_dir(files, path):
    for f in files:
        if f.endswith('.cpp'):
            shutil.rmtree(path)


for t in targets:


    projs = os.listdir(t)
    for p in projs:
        p_path = f'{t}/{p}'
        files = os.listdir(p_path)
        remove_dir(files, p_path)

    projs = os.listdir(t)
    for p in projs:
        p_path = f'{t}/{p}'
        os.makedirs(f'{p_path}/preprocessed', exist_ok=True)

        os.system(f'cp iaed_p1/1/Makefile {p_path}')
        os.system(f'cp iaed_p1/1/preprocessed/Makefile {p_path}/preprocessed')
        os.system(f'rm -r {p_path}/symbolic')

    os.system(f'cp -r iaed_p1/symbolic {t}')
    os.system(f'cp iaed_p1/Makefile {t}')
