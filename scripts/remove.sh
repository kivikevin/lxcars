#!/bin/sh
set +e

DIR_CRM=..
DIR_ERP=../../kivitendo-erp

echo "*******************************************" 
echo "Deinstallation LxCars."
echo "Verzeichnis CRM: $DIR_CRM"
echo "Verzeichnis ERP: $DIR_ERP"
echo "*******************************************"

if [ "$1" = "-f" ]; then  ## für fast
	echo "Datenbank lxcars und Datenbankuser www-data werden NICHT gelöscht."
else
    echo "Datenbank lxcars wird nun gelöscht."	
	/usr/bin/sudo -u postgres dropdb lxcars
	echo "*******************************************"
	echo "Datenbankuser www-data wird gelöscht."
	/usr/bin/sudo -u postgres dropuser www-data
	echo "*******************************************"
fi

#Links löschen und *.orig in * umbenennen
## Menü Patch rückgängig machen
if [ -f $DIR_ERP/menus/crm.ini.orig ]; then
   rm $DIR_ERP/menus/crm.ini
   mv $DIR_ERP/menus/crm.ini.orig $DIR_ERP/menus/crm.ini
else
   echo "Error menue.ini.orig nicht gefunden"
fi
 

## Bild löschen 
if [ -f $DIR_ERP/image/kivitendo.png.orig ]; then
   rm $DIR_ERP/image/kivitendo.png  
   mv $DIR_ERP/image/kivitendo.png.orig $DIR_ERP/image/kivitendo.png
else
   echo "Error kivitendo.png.orig nicht gefunden"
fi 
 
## Icons löschen
if [ -f $DIR_ERP/image/icons/16x16/LxCars--Schnellsuche.png ]; then
   rm $DIR_ERP/image/icons/16x16/LxCars*  
else
   echo "Error $DIR_ERP/image/icons/16x16/LxCars* nicht gefunden"
fi
if [ -f $DIR_ERP/image/icons/24x24/LxCars--Schnellsuche.png ]; then
   rm $DIR_ERP/image/icons/24x24/LxCars*  
else
   echo "Error $DIR_ERP/image/icons/24x24/LxCars* nicht gefunden"
fi
if [ -f $DIR_ERP/image/icons/32x32/LxCars--Schnellsuche.png ]; then
   rm $DIR_ERP/image/icons/32x32/LxCars*  
else
   echo "Error $DIR_ERP/image/icons/32x32/LxCars* nicht gefunden"
fi


echo "done!!"

exit 0
