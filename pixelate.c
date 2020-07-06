#include <stdio.h>
#include <stdlib.h>

#include <vips/vips.h>

int pixelate(const char *, const char *, double, int);

int main(int ac, char *as[]){
    if(ac<3){
        fprintf(stderr, "Usage: %s [infile] [outfile] [?scale] [?quality]\n", as[0]);
        return EXIT_FAILURE;
    }
    double scale=0.2;
    int quality=24;
    if(ac>3)
        sscanf(as[3], "%lf", &scale);
    if(ac>4)
        sscanf(as[4], "%d", &quality);
    

    if(VIPS_INIT(as[0]))
        vips_error_exit(NULL);

/*    
    vips_leak_set(TRUE);
    vips_cache_set_trace(TRUE);
    vips_cache_set_dump(TRUE);
*/
 
    if(!pixelate(as[1], as[2], scale, quality))
        vips_error_exit(NULL);
    
    vips_shutdown(); 
    return EXIT_SUCCESS;
}


int pixelate(const char *infile, const char *outfile, double scale, int quality){
    VipsImage *inp=NULL, *midp=NULL, *outp=NULL;

    if((inp=vips_image_new_from_file(infile, "memory", TRUE, NULL)) == NULL){
        fprintf(stderr, "Error while loading file \"%s\"!\n", infile);
        goto fail;
    }
    
    if(vips_resize(inp, &midp, scale, "kernel", VIPS_KERNEL_NEAREST, NULL)){
        fprintf(stderr, "Error while scaling out!\n");
        goto fail;
    }

    g_object_unref(inp); 
 
    if(vips_resize(midp, &outp, 1.0/scale, "kernel", VIPS_KERNEL_NEAREST, NULL)){
        fprintf(stderr, "Error while scaling in!\n");
        goto fail;
    }
    
    g_object_unref(midp);

    if(vips_pngsave(outp, outfile, "palette", TRUE, "Q", quality, NULL)){
        fprintf(stderr, "Error while writing to file \"%s\"\n", outfile);
        goto fail;
    }

    g_object_unref(outp); 
        
    return 1;

    fail:

    if(inp != NULL) g_object_unref(inp);
    if(midp != NULL) g_object_unref(midp);
    if(outp != NULL) g_object_unref(outp);
    
    return 0;
}
