#!/bin/bash

# Passo 1: Reconfigurar e compilar
echo "🔄 Configurando e compilando com Meson..."
meson setup builddir --reconfigure
meson compile -C builddir || exit 1

# Passo 2: Encontrar e correr todos os testes
#echo "🚀 A correr todos os testes em subdiretórios de ch2_structs..."

# Percorre todos os ficheiros executáveis dentro de builddir/ch2_structs/
#find builddir/ch2_structs -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;


#echo "🚀 A correr todos os testes em subdiretórios de ch3_pointers..."

# Percorre todos os ficheiros executáveis dentro de builddir/ch3_pointers/
#find builddir/ch3_pointers -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;


#echo "🚀 A correr todos os testes em subdiretórios de ch4_enums..."

# Percorre todos os ficheiros executáveis dentro de builddir/ch3_pointers/
#find builddir/ch4_enums -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;


#echo "🚀 A correr todos os testes em subdiretórios de ch5_unions..."

# Percorre todos os ficheiros executáveis dentro de builddir/ch3_pointers/
#find builddir/ch5_unions -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;



#echo "🚀 A correr todos os testes em subdiretórios de ch6_stack_heap..."

# Percorre todos os ficheiros executáveis dentro de builddir/ch3_pointers/
#find builddir/ch6_stack_heap -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;



echo "🚀 A correr todos os testes em subdiretórios de ch7_advanced_pointers..."

find builddir/ch7_advanced_pointers -type f -perm +111 -exec echo "▶️ A correr {}" \; -exec {} \;
