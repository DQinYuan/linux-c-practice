#include <stdio.h>
#include <dlfcn.h>

int main(void)
{
    void	*handle;
    char	*error;
    void	(*welcome)( );

    if ((handle = dlopen("./libttt.so", RTLD_LAZY)) == NULL)
    {
        printf ("dlopen error\n");
        exit (1);
    }

    welcome = dlsym(handle, "welcome");
    if ((error = dlerror()) != NULL)
    {
        printf ("dlsym error\n");
        exit (1);
    }

    welcome ();

    dlclose (handle);

    exit (0);
}
