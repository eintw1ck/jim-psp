rm -f psp_autohle.c psp_autohle_hooks.c psp_autohle.h

echo "#include <stdint.h>" >> psp_autohle.h
for i in `find -name "psp_hle_*"`;do grep "void HLE_" $i | sed -e 's/$/;/g';done >> psp_autohle.h
for i in `find -name "psp_hook_*"`;do grep "void HLE_" $i | sed -e 's/$/;/g';done >> psp_autohle.h

echo "PSP_Syscall pspsyscalls[]={" >> psp_autohle.c
rm -f psp_autohle.c.tmp
for i in `find -name "psp_hle_*"`;do grep "SYSCALL" $i  | sed -e 's/);$/},/g' | sed -e 's/^SYSCALL(/{/g' >> psp_autohle.c.tmp;done
sort psp_autohle.c.tmp  >> psp_autohle.c
rm -f psp_autohle.c.tmp
echo "};" >> psp_autohle.c

echo "PSP_Hook pspmemhooks[]={" >> psp_autohle_hooks.c
rm -f psp_autohle.c.tmp
for i in `find -name "psp_hook_*"`;do grep "MEMHOOK" $i  | sed -e 's/);$/},/g' | sed -e 's/^MEMHOOK(/{/g' >> psp_autohle.c.tmp;done
sort psp_autohle.c.tmp  >> psp_autohle_hooks.c
rm -f psp_autohle.c.tmp
echo "};" >> psp_autohle_hooks.c

rm -f psp_autohle.c.tmp
