/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 10:08:59 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 10:09:03 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_LOADER_H
# define BMP_LOADER_H

# include <stdint.h>

# define FILE_E1				"Error opening file"
# define HEADER_E1				"Error reading bmp header"
# define HEADER_E2				"Bad BMP header!\n"
# define HEADER_E3				"Error reading dib header"
# define COMPRESSION_E1			"Unsupported compression method!\n"
# define BPP_E1					"BMP must have 24 bpp!\n"
# define MALLOC_E1				"Failed to allocate BMP image"
# define DATA_E1				"Failed to read BMP data"
# define DATA_E2				"Failed to read data padding"
# define BI_RGB					0
# define BMP_HEADER_SIZE		14
# define DIB_HEADER_SIZE		40

typedef struct					s_bmp
{
	int							fd;
	unsigned char				bmp_header[BMP_HEADER_SIZE];
	uint32_t					bmp_size;
	uint32_t					data_offset;
	unsigned char				dib_header[DIB_HEADER_SIZE];
	uint32_t					width;
	uint32_t					height;
	uint16_t					bpp;
	uint32_t					compression;
	uint32_t					raw_bmp_size;
}								t_bmp;

void							*load_bmp(char const *filename, t_bmp *bmp_ret);

#endif
