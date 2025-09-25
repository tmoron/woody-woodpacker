#include "woody_woodpacker.h"

Elf64_Ehdr fill_64header(uint64_t entrypoint)
{
	//initialise elf header for 64 bytes
	Elf64_Ehdr header;

	ft_bzero(&header, sizeof(header));
	header.e_ident[EI_MAG0] 		= ELFMAG0;
	header.e_ident[EI_MAG1] 		= ELFMAG1;
	header.e_ident[EI_MAG2] 		= ELFMAG2;
	header.e_ident[EI_MAG3] 		= ELFMAG3;
	header.e_ident[EI_CLASS] 		= 0x02;
	header.e_ident[EI_DATA] 		= 0x01;
	header.e_ident[EI_VERSION] 		= 0x01;
	header.e_ident[EI_OSABI] 		= 0x00;
	header.e_ident[EI_ABIVERSION] 	= 0x00;

	header.e_type 		= 0x02;
	header.e_machine	= 0x3e;
	header.e_version	= 0x01;
	header.e_entry		= entrypoint;
	header.e_phoff		= 0x40;
	header.e_shoff		= 0x00; //TODO: verify
	header.e_flags		= 0x00;
	header.e_ehsize		= 0x64;
	header.e_phentsize	= 0x38; //TODO: verify
	header.e_phnum		= 0x00; //TODO: verify
	header.e_shentsize	= 0x40; //TODO: verify
	header.e_shnum		= 0x00; //TODO: verify
	header.e_shstrndx	= 0x00; //TODO: verify

	return header;
}