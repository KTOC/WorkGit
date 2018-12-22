#!/bin/bash
   #echo $#
   if [ $# != 2 ]; then
      echo -e "\033[31mplease input projectname platform (e.g build_release.sh demo_test mt8765)\033[0m"
      kill 0
   fi
   #��Ŀ�� 
   projectname=$1
   
   #ƽ̨���� ����mt6737  mt6739
   platform=$2
   if [[ "$platform" != "mt8765" ]];  then 
      echo -e "\033[31mplease  input projectname platform (e.g build_release.sh demo_test mt8765)\033[0m"
      kill 0
   fi
   
   #��ȡ��Ŀ����·��
   bigproject=${projectname%%_*}
   path=${platform}/${bigproject}/${projectname}
   src=./eiot/project/${path}
   if [ ! -d  "$src" ]; then
     echo -e "\033[31m$src not exist\033[0m"
     kill 0
   fi
   
   #������Ŀ��Ϣ 
   #mtkbase mtk�ο���Ŀ����
   #projectname ��ǰ�������Ŀ����
   pjmk=$(find $src -name 'ProjectConfig.mk')
   base=${pjmk%/ProjectConfig.mk}
   base=${base##*/}
   echo $base > mtkbase
   echo "$projectname"> projectname
   
   #����modem
   ./eiot/tools/modem.sh $pjmk $platform
   
   #�������� eiot/driver
   driver=eiot/driver
   cp -ar ${driver}/* ./   
   
   #������Ŀ�����ļ�  eiot/project/xxxxxxx
   cp -ar ${src}/* ./
  