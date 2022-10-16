call streams.exe --compress input.txt input_compressed.txt
call streams.exe --encrypt 100500 input.txt input_crypted.txt
call streams.exe --encrypt 100500 --compress input.txt input_crypted_compressed.txt

call streams.exe --encrypt 100500 input.txt output_crypted.txt
call streams.exe --decrypt 100500 input_crypted.txt output_decrypted.txt

call streams.exe --compress input.txt output_compressed.txt
call streams.exe --decompress input_compressed.txt output_decompressed.txt

call streams.exe --encrypt 100500 --compress input.txt output_crypted_compressed.txt
call streams.exe --decrypt 100500 --decompress input_crypted_compressed.txt output_decrypted_decompressed.txt