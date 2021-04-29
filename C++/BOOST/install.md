# boost安装

## 编译安装

1. 到[此处](https://d29vzk4ow07wi7.cloudfront.net/aeb26f80e80945e82ee93e5939baebdca47b9dee80a07d3144be1e1a6a66dd6a?response-content-disposition=attachment%3Bfilename%3D%22boost_1_75_0.tar.gz%22&Policy=eyJTdGF0ZW1lbnQiOiBbeyJSZXNvdXJjZSI6Imh0dHAqOi8vZDI5dnprNG93MDd3aTcuY2xvdWRmcm9udC5uZXQvYWViMjZmODBlODA5NDVlODJlZTkzZTU5MzliYWViZGNhNDdiOWRlZTgwYTA3ZDMxNDRiZTFlMWE2YTY2ZGQ2YT9yZXNwb25zZS1jb250ZW50LWRpc3Bvc2l0aW9uPWF0dGFjaG1lbnQlM0JmaWxlbmFtZSUzRCUyMmJvb3N0XzFfNzVfMC50YXIuZ3olMjIiLCJDb25kaXRpb24iOnsiRGF0ZUxlc3NUaGFuIjp7IkFXUzpFcG9jaFRpbWUiOjE2MTk0MjI0Mjl9LCJJcEFkZHJlc3MiOnsiQVdTOlNvdXJjZUlwIjoiMC4wLjAuMC8wIn19fV19&Signature=hXq8dETsV4fMVuuf~pDz9KQc8YV~Y5P5lspELS4jJHIspDNOT0aQWR4SoFAVZ6zRS51aOgfF07N4bsb0R9cEiIqhZH1GSD-kQjh-VfOxxxFxeuVQZVCzwJJDWvJbRb-uuKlNDEDSVpgty~Xu5dxNGy5xLif9bTbvPc2mkDsqODaaaqDclGDyBAxzT8e2b4bHpBGF5qSBW4MAPtuER4EIkUf9n01c1WerKT3WIurK0c1oxyGbjwvxNlo2a3zua2T8hAiYX7816rdy9MZ0~6X4SHMP-RrP49VvTS6OS1nvRejeICbejc9fKb1m7H6TZzrVew~701iUdtOzShNuJmSnNw__&Key-Pair-Id=APKAIFKFWOMXM2UMTSFA)下载二进制包

2. 解压

   ```c++
   tar -zxvf boost_1_75_0.tar.gz
   ```

3. 运行bootstrap.sh

   ```c++
   ./bootstrap.sh
   ```

4. 编译安装

   ```c++
   sudo ./b2 --buildtype=complete install # 安装所有库
   ```

   

