/*
Cheat on the POSIX C API.

The POSIX C API is mostly an extension of the ANSI C API.
ANSI C features shall not be discussed here.

# Implementations

    On most Linux systems as of 2013, the POSIX C API is implemented by the GNU C library:
    <http://www.gnu.org/software/libc/>.

    The GNU documentation states that POSIX compliance
    is a design goal of the GNU C library.

    # windows

        TODO Is there a Windows implementation for the POSIX C API? Official?
*/

#include "common.h"

int main(void) {
    /*
    # Namespace

        POSIX adds many further per header reserved names which it would be wise to follow even on ANSI C:
        http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html> section "The Name Space"
    */

    /*
    # errors

        Typical error dealing conventions POSIX are:

        - if the return value is not needed, functions return 0 on successs and either -1 on failure
            or an integer which indicates failure cause

        - if the return value is strictly positive, return -1 on error

        - if the return value is a pointer, return `NULL` on error

        - if the return value can be any integer (`ptrace` for example), return `-1`, but force the user to
            clear `errno` before making the call, and check if `errno != -` after the call.

        Whenever there is an error, set `errno` accordingly to determine what was the cause of the erro

    # errno.h

        Is defined by ANSI C, but more predefined error constants are added extended in POSIX,

        Only differences from ANSI C shall be commented here. Note that errno,
        perror and strerror for example are all in ANSI C.

        Some of the POSIX specific errors and their error messages are:

        -   `EPERM`: Operation not permitted

            When users try to do something which requires previledges that they don't have,
            such as being the root user.

        -   `ENOENT`: No such file or directory

        -   `EINTR`: Interrupted system call

        -   `EIO`: I/O Error

        -   `EBUSY`: Device or resource busy

        -   `EEXIST`: File exists

        -   `EINVAL`: Invalid argument

        -   `EMFILE`: Too many open files

        -   `ENODEV`: No such device

        -   `EISDIR`: Is a directory

        -   `ENOTDIR`: Isn’t a directory

        Functions that modify errno document that. The convention is that only functions which fail modify
        errno, not those that succeed.

        errno can be modified as `errno = 0` for example.
    */
    {
        /*
        # errno

            `errno` can be modified by functions to contain a description of certain
            standard errors.

            `errno` is a lvalue and users can explicitly modify it.
            This is necessary in certain error checking situations, when the error can only be decided
            by changes in errno and not by the return value.

            `0` indicates no `error` (ANSI C).

            Since many function may change errno, you must use the functions that
            depend on errno immediatelly after the function that generates the error.
        */
        {
            char *dirname = "i_dont_exist";

            /* Assure that dirname does not exist. */
            if(access(dirname, F_OK) == 0)
                assert(rmdir(dirname) != -1);
            errno = 0;

            rmdir(dirname);
            assert(errno != 0);

            /* Successful calls do *not* set errno to 0. */
            mkdir(dirname, 0777);
            rmdir(dirname);
            assert(errno != 0);
        }
    }

    /*
    # printf

        This discusses `printf` and `sprintf` POSIX extensions to ANSI.
    */
    {
        /*
        # dollar

            `%2$d` means: use second argument. Treat the following arguments as if this one did not exist.

            Has been incorporated in POSIX, but may break ANCI C code! (unlikely).

            For that reason, compiling this generates warnings on gcc, and you should avoid this feature as:

            - it is unlikely to be incorporated in ANSI C since it is a breaking change

            - if you ever decide to increase portability to ANSI C
                (in case some other key functions you were using someday get ANSI C alternatives),
                you will have to correct this
        */
        {
            /*
            char buf[256];
            sprintf(buf, "%2$d %d %d", 0, 1);
            assert(strcmp(buf, "1 0 1") == 0);
            */
        }
    }

    /*
    # math.h

        The `M_PI` constants are defined by POSIX inside of `math.h`.
    */
    {
        /* # constants */
        {
            /* ANSI C way of calculating some constants. */
            const float PI = acos(-1);
            const float E = exp(1);

            /* POSIX provides macros that expand to those constants. */
            assert(fabs(M_E      - E     ) < 1e-6);
            assert(fabs(M_PI     - PI    ) < 1e-6);
            assert(fabs(M_PI/2.0 - M_PI_2) < 1e-6);
            assert(fabs(M_PI/4.0 - M_PI_4) < 1e-6);
        }

        /*
        # bessel

            As of POSIX 7, the only major function addition to the math library
            seems to be Bessel functions.

            TODO understand, specially why is it so important to be here?

            http://en.wikipedia.org/wiki/Bessel_function
        */
        {
            /*
            double j0(double);
            double j1(double);
            double jn(int, double);
            */
        }
    }

    /*
    # string functions

        POSIX offers some extra convenience functions to common string
        operations which are not present in ANSI C.
    */
    {
        /*
        # strfmon

            Monetary string formatting.
        */
        {
            const int size = 16;
            char out[size];
            strfmon(out, size, "%n", 1234.567);
            printf("%s", out);
            assert(strcmp(out, "1234.57") == 0);
        }
    }

    /*
    # strings.h
    */
    {
        /*
        # ffs

            Find First bit Set.

            Has assembly support in many processors, e.g. `bsf` in x86.

            https://en.wikipedia.org/wiki/Find_first_set
        */
        {
            assert(ffs(0) == 0);
            assert(ffs(1) == 1);
            assert(ffs(2) == 2);
            assert(ffs(3) == 1);
        }
    }

    /*
    # File IO

    # File descriptors

        `int` identifier to a data stream.

        Many file descriptors can point to a single file.

        One very important property of file descriptors is the current position from which read and write shall operate.
        Reads and writes move the current position forward.

        # File descriptors vs ANSI C FILE objects

            ANSI C supports only the concept of file pointers via the `FILE` macro.

            POSIX extends ANSI C and contains both function that manipulate ANSI C `FILE` objects
            and file descriptors, which are integers that identify a file descriptor for the OS.

            Operations that use file desriptors:

            - open, close, write

            Operations that use FILE pointers:

            - ANSI C `fopen`, `fclose`, `ftell`, etc. functions

            Since they are specific to POSIX, functions that use file pointers often give more options
            than ANSI C functions that use `FILE*` objects.

            If you don't need that greater level of control,
            just use the ANSI C functions for greater portability.

            It is possible to convert freely to and from `FILE*` via fdopen and fileno.

    # fdopen

        Convert file descriptor to `FILE*`.

    # fileno

        Convert `FILE*` to file descriptor.

    # open

            man 2 open

        Open file descriptors such as files

        Returns an `int` (file descriptor number) instead of a file.

        Interfaces:

            int open(const char *pathname, int flags);
            int open(const char *pathname, int flags, mode_t mode);

        Flags. Must specify one and only of the following:

        -   `O_WRONLY`: write only

        -   `O_RDONLY`: read only.

            Undefined behaviour with O_TRUNC.

            TODO can be used with O_CREAT?

        -   `O_RDWR`: read and write

        Other important flags.

        -   `O_APPEND`: If the file exists, open fd at the end of the file.

        -   `O_TRUNC`: If the file exists, open fd at the end of the file,
            set its length to zero, discarding existing contents.

            Undefined behaviour with O_RDONLY.

        -   `O_CREAT`: If the file does not exit, creat it, with permissions given in mode.

            Mode must be specified when this flag is set, and is ignored if this is not set.

        -   `O_EXCL`: Used with O_CREAT, ensures that the caller creates the file.

            The open is atomic; that is, no two opens can open at the same time.

            If the file already exists, open will fail.

            Useful if multiple programs may try to create the same file.

        Mode can be specified via oring predefine permission values of type:

        - S_IRWXU  00700 user (file owner) has read, write and execute permission
        - S_IRUSR  00400 user has read permission
        - S_IWUSR  00200 user has write permission
        - S_IXUSR  00100 user has execute permission

        For group and other: G and GRP, O and OTH.

        Return value: `-1` on error and set perror.

    # creat

        Same as:

            open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);

    # close

        File descriptors occupy memory and are thus a finite resource.

        When you are done with one, release it with a close call.

    # write

        Write to file descriptor, such as one representing a file gotten via `open`
        or one representing a pipe obtained with `pipe`.

        Increments the current position of the file descriptor.
        For regular files, if this becomes greater than the current file size,
        then the file size is increased as needed.

        # return value

            Returns number of bytes writen.

            For regular files, POSIX does not say much when the number of bytes writen is less than the ammount required
            and that usually only happens in bad cases:

            - signal received in the middle of a write

                If it receives a signal before writing anything, returns -1.

            - no more space in the filesystem

            - no permission to write such large files

            For pipes, this may occur in less bad scenarios, for example if the pipe buffer is filled,
            the write may either:

            - be partial if `nbytes > PIPE_BUF`

            - block until more space is available depending on the `O_NONBLOCK` state.

            On error, return -1 and set errno.

            It seems that POSIX does not say if zero return values on non-zero size write requests.
            It is unlikely that an implementation will return 0, since that would make no progress,
            and it should return `-1` and set errno instead to report error cases.

        # atomicity of simultaneous writes

            Writes of less than `PIPE_BUF` bytes cannot be interleaved with other writes.

            Larger writes can.

        TODO0 are writes to seekable files atomic? Seems not: <http://stackoverflow.com/questions/10650861/atomicity-of-write2-to-a-local-filesystem>
            for pipes we know yes for writes smaller than PIPE_BUF.

    # pwrite

        Same as write, but writes to a given offset and does not update fd position.

        It cannot be done on non seekable files.

    # read

        POSIX 7 docs: http://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html

        Read bytes from a file descriptor.

        Interface:

            ssize_t read(int fildes, void *buf, size_t nbyte);

        The behavior of multiple concurrent reads on the same pipe, FIFO, or terminal device is unspecified.

        If the starting position is at or after the end-of-file, 0 shall be returned.

        If the value of `nbyte` is larger than {SSIZE_MAX}, the result is implementation-defined.
        In practice this is rarely the case, because `SSIZE_MAX` is the size of a `size_t` type,
        which is usually an integer, giving around 2Gb.

        The exact behaviour of read depends on the fd type: pipes and regular files have slightly different rules.

        # read pipe

            When attempting to read from an empty pipe or FIFO:

            - If no process has the pipe open for writing, read() shall return 0 to indicate end-of-file.

            - If some process has the pipe open for writing and O_NONBLOCK is set,
                read() shall return -1 and set errno to [EAGAIN].

            - If some process has the pipe open for writing and O_NONBLOCK is clear,
                read() shall block the calling thread until some data is written or
                the pipe is closed by all processes that had the pipe open for writing.

        # return value

            Returns number of bytes read.

            Quoting POSIX:

            The value returned may be less than nbyte if:

            - the number of bytes left in the file is less than nbyte

            - the read() request was interrupted by a signal

            - if the file is a pipe or FIFO or special file and has fewer
                than nbyte bytes immediately available for reading.

            Therefore on a regular file, this is how the end of file can be recognized.

            On error return -1 and set errno.

    # lseek

        Like ANSI C fseek for file descriptors.

        lseek cannot be done on certain file descriptor types which are not seekable,
        for example on pipes.

        # lseek after eof

            If data is writen with offset after file size, file size is increased and data skipped reads `(int)0` (`'\0'`).

            This contrasts with ANSI C fseek, in which this is undefined behaviour.
    # fcntl

        Manipulate a file descriptor.

        Check if a fd is open: <http://stackoverflow.com/questions/12340695/how-to-check-if-a-given-file-descriptor-stored-in-a-variable-is-still-valid>

    # dup

        Duplicate file descriptor.

        Same as:

            fcntl(fildes, F_DUPFD, 0);

    # send

        Generalization of write:

        <http://pubs.opengroup.org/onlinepubs/9699919799/functions/send.html>

        TODO

    # recv

        Generalization of read:

        <http://pubs.opengroup.org/onlinepubs/9699919799/functions/recv.html>

        TODO
    */
    {
        int fd;
        char in[] = "abcd";
        int nbytes = strlen(in);
        char *out = malloc (nbytes + 1);
        char *fname = TMPFILE("open");

        /* BAD forget O_CREAT on non-existent file gives ENOENT */
        {
            fd = open("/i/do/not/exist", O_RDONLY, S_IRWXU);
            if (fd == -1) {
                assert(errno == ENOENT);
            } else {
                assert(false);
            }
        }

        /* BAD write on a O_RDONLY fd gives errno EBADF */
        {
            int fd;
            char *fname = TMPFILE("write_rdonly");

            fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            } else {
                if (close(fd) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
            }

            fd = open(fname, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            } else {
                if (write(fd, "a", 1) == -1) {
                    assert(errno == EBADF);
                } else {
                    assert(false);
                }
                if (close(fd) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
            }
        }

        /*
        Open and write without truncate.

        Output:

            after write 1: abcd
            after write 2: 01cd
        */
        {
            /* Set file to `abc`. */
            {
                fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
                if (fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                } else {
                    if (write(fd, in, nbytes) != nbytes) {
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                    if (close(fd) == -1) {
                        perror("close");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            /* Open and write to it without truncating. */
            {
                fd = open(fname, O_RDWR);
                if (fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                } else {
                    if (write(fd, "01", 2) != 2) {
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            /* Check the new result. */
            {
                if (lseek(fd, 0, SEEK_SET) != 0) {
                    perror("lseek");
                    exit(EXIT_FAILURE);
                }
                if (read(fd, out, nbytes) != nbytes) {
                    perror("read");
                    exit(EXIT_FAILURE);
                } else {
                    /* The first two bytes were overwriten. */
                    assert(memcmp(out, "01cd", nbytes) == 0);
                }
                if (close(fd) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }
        }

        /*
        `lseek` after EOF
        */
        {
            int fd;
            char out[2];

            fd = open(TMPFILE("lseek"), O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            } else {
                if (lseek(fd, 1, SEEK_SET) != 1) {
                    perror("lseek");
                    exit(EXIT_FAILURE);
                }
                if (write(fd, "a", 1) != 1) {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
                /* Read after eof, return 0 and read nothing. */
                if (read(fd, out, 1) != 0) {
                    assert(false);
                }
                if (lseek(fd, 0, SEEK_SET) != 0) {
                    perror("lseek");
                    exit(EXIT_FAILURE);
                }
                /* Byte 0 was never writen, so reading it returns `(int)0`. */
                if (read(fd, out, 2) != 2) {
                    perror("read");
                    exit(EXIT_FAILURE);
                } else {
                    assert(memcmp(out, "\0a", 2) == 0);
                }
                if (close(fd) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                }
            }
        }

        /*
        File descriptors open by default to all processes.

        Analogous to ANSI C `stdout`, `stdin` and `stderr`, except that the ANSI C `FILE*` objects.

        # STDIN_FILENO

            stdin

        # STDOUT_FILENO

            stdout

        # STDERR_FILENO

            stderr
        */
        {
            printf("STDIN_FILENO  = %d\n", STDIN_FILENO);
            printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
            printf("STDERR_FILENO = %d\n", STDERR_FILENO);
        }

        /*
        # aio family

        # Asynchronous IO

        # aio_cancel

        # aio_error

        # aio_fsync

        # aio_read

        # aio_return

        # aio_suspend

        # aio_write

        Great soruce: <http://www.fsl.cs.sunysb.edu/~vass/linux-aio.txt>

        In Linux, implemented with the system calls:

            io_cancel(2)                2.6
            io_destroy(2)               2.6
            io_getevents(2)             2.6
            io_setup(2)                 2.6
            io_submit(2)                2.6
        */
        {
            /* TODO */
        }
    }

    /*
    # link

        Create hardlink to file.

        If newfile exists, the link is not created, returns -1 and sets `errno = EEXIST`

    # unlink

        Delete file.

        Is called unlink because what you are doing is not to directly remove a file from disk
        but instead remove one hardlink for the data.

        If the number of hardlinks to a data equals 0, it the data gets deleted.

        If the given path does not exist `errno = ENOENT`.
    */
    {
        int fd;
        char in[] = "a";
        char in_new[] = "b";
        int nbytes = strlen(in);
        char *out = malloc(nbytes);
        char *oldpath = TMPFILE("link_old");
        char *newpath = TMPFILE("link_new");

        /* Create old. */
        fd = open(oldpath, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        } else {
            if (write(fd, in, nbytes) != nbytes) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            if (close(fd) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }

        /* Ensure that the new path does not exist */
        /* `ENOENT` is ok since the path may not exist */
        if (unlink(newpath) == -1 && errno != ENOENT) {
            perror("link");
            exit(EXIT_FAILURE);
        }

        /* Make the hardlink. */
        if (link(oldpath, newpath) == -1) {
            perror("link");
            exit(EXIT_FAILURE);
        }

        /* Write to new. */
        fd = open(newpath, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        } else {
            if (write(fd, in_new, nbytes) != nbytes) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            if (close(fd) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }

        /* assert that it reflected on old */
        fd = open(oldpath, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        } else {
            if (read(fd, out, nbytes) != nbytes) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            assert(memcmp(out, in_new, nbytes) == 0);
            if (close(fd) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }

        free(out);
    }

    /* # Pathname operations */
    {
        /*
        # realpath

            Return:

            - absolute path
            - cannonical: does not contain `.` nor `..`.

            Interface:

                char *realpath(const char *restrict file_name,
                    char *restrict resolved_name);

            The function does completelly different things depending if resolved_name is NULL or not:

            -   `resolved_name == NULL`: realpath mallocs the path for you and returns it.

                You have to free it in the future.

                This is a good options if you don't already have a buffer of the right size, since calculating the required buffer size
                would be annoying (would require calling `pathconf`).

            -   `resolved_name == NULL`: the pathname is copied to `resolved_name`.

                You must make sure that you have enough space there.

                This is a good option if you already have a large enough buffer laying around,
                since it does not require dynamic allocation.

                Of course, ensuring that your buffer is large enough means doing messy `pathconfs` at some point.
        */
        {
            char *rp = realpath(".", NULL);
            if (rp) {
                printf("realpath(\".\") = %s\n", rp);
            } else {
                perror("realpath");
                exit(EXIT_FAILURE);
            }
            free(rp);
        }

        /*
        # dirname # basename

            p may be modified memory is statically allocated
            and may change on next dirname/basename call.
            TODO what is p

            behaviour:

            path         dirname   basename
            ----------   --------  ---------
            "/usr/lib"   "/usr"    "lib"
            "/usr/"      "/"       "usr"
            "usr"        "."       "usr"
            "/"          "/"       "/"
            "."          "."       "."
            ".."         "."       ".."
        */
        {

            char p[1024];
            char* res;

            strcpy(p, "a/b");
            res = dirname(p);
            assert(strcmp(res, "a") == 0);

            strcpy(p, "a/b");
            res = basename(p);
            assert(strcmp(res, "b") == 0);
        }
    }

    /*
    # getrlimit

        Returns the maximum value for a given resource.

        Linux has a system call with that name.

        There are two types of limits:

        - soft: can be increased by any process to any value lower than the hard maximum
        - hard: only processes with special privileges may increase the hard limit

        If a resource goes over the soft limit, the kernel may choose to kill the process

        Interfaces:

            int getrlimit(int resource, struct rlimit *rlp);
            int setrlimit(int resource, const struct rlimit *rlp);

        -   resource: see the docs for a description of each possible value

        -   rlp: struct of type:

                struct rlimit {
                    rlim_t rlim_cur  // The current (soft) limit.
                    rlim_t rlim_max  // The hard limit.
                }

            where `rlim_t` is an unsigned integer
    */
    {
        struct rlimit limit;
        if (getrlimit(RLIMIT_DATA, &limit) == -1) {
            perror("getrlimit(RLIMIT_DATA, ...) failed");
            exit(EXIT_FAILURE);
        } else {
            /* maximum process memory in bytes */
            if (limit.rlim_max == RLIM_INFINITY) {
                /* RLIM_INFINITY means that no limit is imposed on the resource */
                puts("RLIMIT_DATA: no limit imposed");
            } else {
                printf(
                    "RLIMIT_DATA\n  soft = %ju\n  hard = %ju\n",
                    (uintmax_t)limit.rlim_cur,
                    (uintmax_t)limit.rlim_max
                );
            }
        }

        /* OK, enough of error checking from now on. */
        printf("RLIM_INFINITY = %ju\n", (uintmax_t)RLIM_INFINITY);

        /* maximum total CPU usage in seconds. */
        getrlimit(RLIMIT_CPU, &limit);
        printf(
            "RLIMIT_CPU\n  soft = %ju\n  hard = %ju\n",
            (uintmax_t)limit.rlim_cur,
            (uintmax_t)limit.rlim_max
        );

        /* Maximum file size in bytes. */
        getrlimit(RLIMIT_FSIZE, &limit);
        printf(
            "RLIMIT_FSIZE\n  soft = %ju\n  hard = %ju\n",
            (uintmax_t)limit.rlim_cur,
            (uintmax_t)limit.rlim_max
        );

        /* Number of file descriptors: */
        getrlimit(RLIMIT_NOFILE, &limit);
        printf(
            "RLIMIT_NOFILE\n  soft = %ju\n  hard = %ju\n",
            (uintmax_t)limit.rlim_cur,
            (uintmax_t)limit.rlim_max
        );
    }

    /*
    # limits.h

        This header exists in ANSI C, and POSIX extends it with several values.

        Defines current and possible maximums and minimums for several resources.

        Some resources cannot cannot be evaluated statically.

        For example the maximum path length depends on which directory we are talking about,
        since different directories can be on different mount points.

        In those cases, limits defines a KEY value which can be passed to a function that gets
        the actual values for a given key, for example pathconf or sysconf.

        For resources that have fixed values, this header furnishes them directly.
    */
    {
        /* Static macros. */
        {
            /* TODO what is it */
            printf("NL_ARGMAX = %d\n", NL_ARGMAX);

            /* Maximum value that fits into a `size_t`. */
            printf("SSIZE_MAX (Mib) = %ju\n", (uintmax_t)SSIZE_MAX / (1 << 20));

        }

        /*
        # maximum path length

            This is needed often when you need to deal with paths names.

            Sources:

            - <http://stackoverflow.com/questions/2285750/size-of-posix-path-max>

            Keep in mind that this value can vary even while a program is running,
            and depends of the underlying filesystem, and therefore of the direcotory you are in.

            As a consequence of this, it does not make sense to have a macro constant and use it to create
            fixed variable arrays: a function is needed, and memory must be allocated with malloc.

        # pathconf

            Similar to sysconf, but for parameters that depend on a path, such as maxium filename lengths.
        */
        {
            /* Max basename in given dir including trailling null: */
            printf("pathconf(\".\", _PC_NAME_MAX) = %ld\n", pathconf(".", _PC_NAME_MAX));

            /* Max pathname in (TODO this is per device?) */
            printf("pathconf(\".\", _PC_PATH_MAX) = %ld\n", pathconf(".", _PC_PATH_MAX));
        }
    }

    /*
    # user information

        Once use have uids for processes, you can querry standard user information
        which was traditionally stored in the `/etc/passwd` file.
    */
    {
        /*
        # getpwuid

            You can get those information either by username or by uid:

                # include <pwd.h>

                struct passwd *getpwuid(uid_t uid);
                struct passwd *getpwnam(const char *name);

            The struct returned is:

                struct passwd {
                    passwd Member    // Description
                    char *pw_name    // The user’s login name
                    uid_t pw_uid     // The UID number
                    gid_t pw_gid     // The GID number
                    char *pw_dir     // The user’s home directory
                    char *pw_gecos   // The user’s full name
                    char *pw_shell   // The user’s default shell
                }

            Which contains all the required user metadata specified by POSIX.
        */
        {
            uid_t uid = getuid();
            struct passwd* info = getpwuid(uid);
            if (info == NULL) {
                perror("getpwuid failed");
                exit(EXIT_FAILURE);
            } else {
                puts("getpwuid");
                printf("  pw_name        = %s\n", info->pw_name );
                printf("  pw_uid         = %d\n", info->pw_uid  );
                printf("  pw_gid         = %d\n", info->pw_gid  );
                printf("  pw_dir         = %s\n", info->pw_dir  );
                printf("  pw_gecos       = %s\n", info->pw_gecos);
                printf("  pw_shell       = %s\n", info->pw_shell);
            }
        }

        /*
        # getpwent

            Iterate a list of all passwd structures.

            First call gets the first, every call gets the next.

            To start from beginning again do:

                void setpwent(void);

            When you are done, free any associated resources with:

                endpwent()
        */
        {
            puts("all users:");
            struct passwd* info;

            info = getpwent();
            while (info != NULL) {
                printf("  %s\n", info->pw_name);
                info = getpwent();
            }
            endpwent();
        }
    }

    /*
    # getpriority

        Each process, user and group has a priority associated to it.

        Those priorities are commonly called *nice* values on UNIX, since
        the higher the nice, the less time it takes (it is nicer to other processes)

        Any process can reduce its priority.
        Only a priviledged process can increaes its priority,
        even if the process just decreased it himself.

        POSIX does not fix the nice range, but it does specify that:

        - lower values are more favorable
        - the values must be between `-{NZERO}` and x{NZERO}-1`.

        where `NZERO` is implementation defined parameter.

        The minimum value for NZERO if 20, it is also the most common.

        The actual effect of priority is undefined.

        `nice`:

            int nice(int incr)

        - incr: how much to increase the nice value
        - return: the new nice value after the increase

        `getpriority`:

            int getpriority(int which, id_t who);

        -   `which`:

            - PRIO_PROCESS:
            - PRIO_PGRP: TODO
            - PRIO_USER: TODO

        -   `who`: pid, uid or gid depending on which. `0` means current.

        # error checking

            On error, returns `-1` and errno set to indicate the error.

            Therefore simply checking the return value is not enough to detect an error
            since `-1` is a valid return value.

            Therefore, to do error checking one *must* check `errno != 0`:

            - set `errno = 0`
            - make the call
            - there is an error iff ret = -1 errno != 0.

    # setpriority

        Return value is the same as getpriority after the modification.

    # nice

        Same as setpriority, but only for `PRIO_PROCESS` but increments
        (or decrements) the value instead of setting it to an absolute value.

        Return value is the same as getpriority after the modification.

        Can only be negative if we have `sudo`, since a negative value means to increase the priority.
    */
    {
        int prio;

        printf("NZERO = %d\n", NZERO);

        errno = 0;
        prio = getpriority(PRIO_PROCESS, 0);
        if (prio == -1 && errno != 0) {
            perror("getpriority(PRIO_PROCESS, 0)");
        } else {
            printf("getpriority(PRIO_PROCESS, 0) = %d\n",  prio);
        }

        errno = 0;
        prio = getpriority(PRIO_PGRP, 0);
        if (prio == -1 && errno != 0) {
            perror("getpriority(PRIO_PGRP, 0)");
        } else {
            printf("getpriority(PRIO_PGRP, 0) = %d\n",  prio);
        }

        errno = 0;
        prio = getpriority(PRIO_USER, 0);
        if (prio == -1 && errno != 0) {
            perror("getpriority(PRIO_USER, 0)");
        } else {
            printf("getpriority(PRIO_USER, 0) = %d\n",  prio);
        }

        errno = 0;
        prio = nice(0);
        if (prio == -1 && errno != 0) {
            perror("nice(0)");
        } else {
            printf("nice(0)    = %d\n",    nice(0));
        }

        /* ok, tired of errno checking: */
        printf("nice(0)    = %d\n",    nice(0));
        printf("nice(1)    = %d\n",    nice(1));
        printf("nice(0)    = %d\n",    nice(0));

        errno = 0;
        prio = nice(-1);
        if (prio == -1 && errno != 0) {
            /* if not root we end up here */
            perror("nice(-1)");
        } else {
            printf("nice(-1)  = %d\n", prio);
        }
    }

    /*
    # sched.h

        Get or set scheduler information

        POSIX 7 specifies four scheduling policies, more can be defined by the implementation

        The precise decription of those policies can be found under System interfaces > Scheduling policies.

        TODO what happens if there is both a FIFO and a RR process running?

        -   `SCHED_FIFO`:

            First in first out. Process runs untill it finishes, blocking the CPU while it runs.

            An infinite loop could be catastrophic.

            In linux, applied to realtime process.

        -   `SCHED_RR`:

            Round robin.

            Assign time slices proportional to prio and turn around the pie.

            In linux, applied to realtime process.

        -   `SCHED_SPORADIC`:

            TODO0

            Optional, so don't rely on it.

        -   `SCHED_OTHER`:

            Any other type of scheduling.

            In linux, includes SCHED_NORMAL, the normal scheduling policy.

            POSIX explicitly says that it is implementation defined what happens
            when there are both process of `SCHED_OTHER` and another type at the same time.

    # sched_getscheduler

        `pid_t` for given pid, `0` for current process

    # sched_get_priority_max

        Get maximum possible priority for a given policy.

    # sched_get_priority_min
    */
    {
        printf("SCHED_FIFO = %d\n", SCHED_FIFO);
        printf("sched_get_priority_max(SCHED_FIFO) = %d\n", sched_get_priority_max(SCHED_FIFO));
        printf("sched_get_priority_min(SCHED_FIFO) = %d\n", sched_get_priority_min(SCHED_FIFO));

        printf("SCHED_RR = %d\n",  SCHED_RR);
        printf("sched_get_priority_max(SCHED_RR) = %d\n", sched_get_priority_max(SCHED_RR));
        printf("sched_get_priority_min(SCHED_RR) = %d\n", sched_get_priority_min(SCHED_RR));

        /*printf("SCHED_SPORADIC = %d\n",  SCHED_SPORADIC);*/

        printf("SCHED_OTHER = %d\n",  SCHED_OTHER);
        printf("sched_get_priority_max(SCHED_OTHER) = %d\n", sched_get_priority_max(SCHED_OTHER));
        printf("sched_get_priority_min(SCHED_OTHER) = %d\n", sched_get_priority_min(SCHED_OTHER));

        printf("sched_getscheduler(0) = %d\n",  sched_getscheduler(0));

        /*
        # sched_setscheduler()

            You need root permissions to change to higher priority modes such as from `SCHED_NORMAL` to `SCHED_FIFO` or `SCHED_RR`.
        */
        {
            int policy = SCHED_FIFO;
            struct sched_param sched_param = {
                .sched_priority = 99
            };

            if (sched_setscheduler(0, policy, &sched_param) == -1) {
                perror("sched_setscheduler");
                /*exit(EXIT_FAILURE);*/
            } else {
                assert(sched_getscheduler(0) == policy);
            }
        }

        /*
        Bogging the computer down.

        Time to have some destructive fun by making your computer bog down because of infinite loops on real time processes.

        This will generate an infinite number of `SCHED_FIFO` classes with maximum priority.

        *SAVE ALL DATA BEFORE DOING THIS!!!*

        Needs root to work.

        I recommend running this with music on the background to see the music break up.
        The mouse also becomes very irresponsive.

        However userspace system does not halt. It seems that POSIX does not specify how operating systems
        should deal with different simultaneous scheduling policies, and my Linux does not let SCHED_FIFO run 100% of the time.
        maybe as explained here: <http://stackoverflow.com/a/10290305/895245>.

        I could therefore kill the parent and all children with a C-C on the starting terminal.
        */
        if (0) {
            int policy = SCHED_FIFO;
            struct sched_param sched_param = {
                .sched_priority = sched_get_priority_max(policy)
            };

            if (sched_setscheduler(0, policy, &sched_param) == -1) {
                perror("sched_setscheduler");
            } else {
                while (1) {
                    pid_t pid = fork();
                    if (pid == -1) {
                        perror("fork");
                        assert(false);
                    } else {
                        if (pid == 0)
                            break;
                    }
                }
                while (1);
            }
        }
    }

    /*
    # IPC

        inter process communication

        the basic ways are:

        at startup:

        - command line arguments
        - environment variables

        during execution:

        - pipes
        - regular files
        - signals
        - shared memory
        - sockets
    */

    /*
    # pipe

        Must read man page:

            man 7 pipe

        Unidirectional data transfer from the write side to the read side.

        The write side in on one process (producer)
        and the read side on another one (consumer).

        The consumer and producer can be the same process, but in that case pipes are useless.

        There are two types of pipes:

        - unnamed pipes
        - FIFOs

        Both pipe sides are represented by either a file descriptor int or by a `FILE*`,
        and many operations on them are the same as operation on disk files using
        functions such as `write` and `read`.

        # Pipes are RAM only

            Pipes are meant to be implementable on RAM only without using the filesystem.

            This means that reading and writing to pipes is potentially much faster
            than reading and writing to files.

            The price to pay is that some operations
            such as `ftell` and `fseek` are not possible.
            There are also fcntl flags which cannot be applied to pipes.

        # Read and write operations on pipes

            Read and write operations may be slightly differnt depending on the file descriptor type.

            This is specially the case for pipes vs regular files with respect to blocking.

            For example, pipes usually block if there is no more data available, and wait for data to become available.

            See the documentation of read and write for the details.

        # Forbidden pipe operations

            Since pipes are meant to be implemented on RAM only, pipes cannot be rewinded.

            For example, using `ftell` on a pipe generate `errno=ESPIPE`.

            Therefore, once the data has been read from the read side it can be discareded by the OS,
            preventing all its RAM from being used up easily.

            It seems that the only way to ask for forgiveness rather than permission and just do a `ftell`.
            <http://stackoverflow.com/questions/3238788/how-to-determine-if-a-file-descriptor-is-seekable>

        # Advantages over using files

            Potentially faster because possible to be RAM only.

            If the read happens before the write it blocks untill the write is done.
            This lets the OS manage all the synchronization.

        # Pipe capacity

            There is a maximum data ammount that can be writen to a pipe.

            If a process tries to write more data than the maximum to the pipe, it blocks until
            part of the data is read.

            This is a good source of deadlocks!

            It seems that it is not possible to get the maximum pipe capacity:
            <http://pubs.opengroup.org/onlinepubs/009695399/functions/write.html#tag_03_866>.
    */
    {
        /*
        # Unnamed pipe

            Can be created either via `popen` or `pipe`

            A single process must start two children process:
            the data source and the data consumer and connect them

            Advantages over named pipes:

            - simple: no need to agree on a filename to communicate over
            - secure: other process cannot se the data as they could in a file

            i think it is not possible to know if a file pointer
            is open for reading or writtin besides looking at how
            it was created

            workflow:

            - child fills the buffer, then parent takes control
            - child fills ...
        */

        /*
        # popen

            <http://pubs.opengroup.org/onlinepubs/9699919799/functions/popen.html>

                man popen

            Conveninence method that does:

            - `fork`
            - `exec`
            - `pipe`

            to / from the current process and a child.

            It is:

            -   more general than `system`, as it allows to either set the stdin of the process,
                or get it's stdout (but not both since pipes are unidirectional)

                As a consequence, unlike `system` it does not automatically wait
                for the command to return on the parent: you must wait for the process to end,
                the most convenient way in thise case being with `pclose`, which takes the
                `FILE*` returned by this function. But the `wait` family would also work
                if you get the child PID.

            -   less general than `pipe`

                The output of popen is put on an unnamed pipe, which is accessible via
                ANSI C FILE type returned by the function, instead of POSIX file descriptor (integers)
                Therefore you must use ANSI C file io functions like `fopen` or `fclose` with it,
                instead of the more low level POSIX `open` or `write` family.

            errno may or not be set depending on what caused the error.

        # pclose

            Wait for process created by `popen` to terminate.

            Returns child exit status if the process was not waited for before,
            `-1` otherwise.
        */
        {
            /* Read from stdout of command and get its exit status. */
            {
                /* popen uses ANSI C fread which uses ANSI C FILE type: */
                FILE *read_fp;
                char buffer[BUFSIZ + 1];
                char cmd[1024];
                int chars_read;
                int exit_status;
                int read_cycles = 0;
                int desired_read_cycles = 3;
                int desired_last_char_read = 1;
                assert(desired_last_char_read < BUFSIZ);

                sprintf(
                    cmd,
                    "for i in `seq %ju`; do echo -n a; done",
                    (uintmax_t)(desired_read_cycles - 1) * BUFSIZ + desired_last_char_read
                );
                read_fp = popen(cmd, "r");
                if (read_fp == NULL) {
                    printf("popen failed\n");
                    exit(EXIT_FAILURE);
                } else {
                    do {
                        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
                        buffer[chars_read] = '\0';
                        printf("======== n bytes read: %d\n", chars_read);
                        /* If you want to see a bunch of 'a's... */
                        /*printf("%s\n", buffer); */
                        read_cycles++;
                    } while (chars_read == BUFSIZ);

                    exit_status = pclose(read_fp);
                    if (exit_status == -1) {
                        printf("pclose failed\n");
                        exit(EXIT_FAILURE);
                    }

                    assert(read_cycles == desired_read_cycles);
                    assert(chars_read == desired_last_char_read);
                    assert(exit_status == 0);
                }
            }

            /* Write to stdin of command, its stdout goes to current stdout. */
            {
                FILE *write_fp;
                char buf[BUFSIZ];
                int exit_status;

                memset(buf, 'b', BUFSIZ);

                /*
                Counts how many charaters were given to stdin
                using many sh features to make it clear that a sh interpreter is called.
                */
                write_fp = popen("read A; printf 'popen write = '; printf $A | wc -c", "w");

                if (write_fp == NULL) {
                    assert(false);
                } else {
                    /* TODO is safe to write twice BUFSIZ without a newline in the middle? */
                    fwrite(buf, sizeof(char), BUFSIZ, write_fp);
                    fwrite(buf, sizeof(char), BUFSIZ, write_fp);

                    /* Print `2 * BUFSIZ` command waits until pipe close. */
                    exit_status = pclose(write_fp);
                    assert(exit_status == 0);
                }
            }
        }

        /*
        # FIFO

            aka named pipes

            appear on the filesystem

            therefore can be accessed as by any process who sees it
            and has enough priviledge level

            are however faster than writting to files,
            since everything happens on RAM

            cannot open for rw

            application: simple client/servers!

            created with mkfifo

        # mkfifo

            Create a FIFO.

        # mknod

            Create a FIFO, character device, block device, directory or file.

                int mknod(const char *path, mode_t mode, dev_t dev);

            POSIX only demands that this work for FIFOs, all other are optional suggested interfaces.

            The type is ored into mode and can be:

                S_IFIFO
                S_IFCHR
                S_IFDIR
                S_IFBLK
                S_IFREG //regular file

            however implementation need only support `S_IFIFO`.

            `dev` represents the device corresponding to the file, and must be `0` in the case of `S_IFIFO`,
            since FIFOs have no associated devices.

            Linux implements all the options except `S_IFDIR` via the `sys_mknod` syscall.
            It also adds `S_IFSOCK` for UNIX domain sockets. Glibc provides a wrapper for all the extended linux
            functionality.
        */
        {
        }

        /*
        # PIPE_BUF

            Maximum size that guarantees that a pipe write operation will be atomic.

            PIPE_BUF is guaranteed to be at least 512.

            See `man 7 pipe` for an explanation.

            Quoting POSIX 7:

                If path refers to a FIFO, or fildes refers to a pipe or FIFO,
                the value returned shall apply to the referenced object.

                If path or fildes refers to a directory, the value returned shall apply to any FIFO that exists
                or can be created within the directory.

                If path or fildes refers to any other type of file,
                it is unspecified whether an implementation supports an association of the variable name with the specified file.

            Conclusions:

            - the PIPE_BUF of an unnamed pipe can only be determined after it is created via `fpathconf`.
            - the PIPE_BUF of FIFOs is the same for all fifos on given directory.

                It can be retreived with `pathconf`.
        */
        {
            long pipe_buf;
            int pipes[2];

            /* unnamed pipe */
            if (pipe(pipes) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            } else {
                pipe_buf = fpathconf(pipes[0], _PC_PIPE_BUF);
                printf("PIPE_BUF pipes[0] = %ld\n", pipe_buf);
                assert(pipe_buf >= 512);

                pipe_buf = fpathconf(pipes[1], _PC_PIPE_BUF);
                printf("PIPE_BUF pipes[1] = %ld\n", pipe_buf);
                assert(pipe_buf >= 512);
            }

            /* directory */
            pipe_buf = pathconf(".", _PC_PIPE_BUF);
            printf("PIPE_BUF \".\" = %ld\n", pipe_buf);
            assert(pipe_buf >= 512);
        }
    }

    /*
    # shared memory

        Memory that can be accessed by multiple separate processes.

        In this example, both parent and child processes access the same shared memory.
    */
    {
        int shmid;
        int *shmem;

        /*
        # shmget

            Allocate shared memory

                int shmget(key_t key, size_t size, int shmflg);

            - key: TODO0 what is this
            - size: num of bytes
            - shmflg: permission flags like for files + other specific flags
                IPC_CREAT is required to allocate the memory

            Return:

            - negative if error
            - unique identifier of memory if positive
        */
        {
            shmid = shmget((key_t)1234, sizeof(int) * 2, IPC_CREAT | S_IRWXU | S_IRWXO);
            assert(shmid >= 0);
        }

        /*
        # shmat

            Attach shared memory to current process so it can be used afterwards

                void *shmat(int shm_id, const void *shm_addr, int shmflg);

            - shm_id: memory id given to shmget
            - shm_id: where to map to. Usual choice: `NULL` so the system choses on its own.
            - shm_flg:
        */
        {
            shmem = shmat(shmid, NULL, 0);
            if (shmem == (void*)-1) {
                assert(false);
            } else {
                shmem[0] = 1;
                fflush(stdout);
                pid_t pid = fork();
                if (pid < 0) {
                    assert(false);
                } else {

                    /* Child only. */
                    if (pid == 0) {

                        /* Child inherits attached memory. */
                        shmem[0]++;

                        /* Detach from child. */
                        assert(shmdt(shmem) == 0);

                        exit(EXIT_SUCCESS);
                    }

                    int status;
                    wait(&status);
                    /* Parent only after child. */
                    assert(status == EXIT_SUCCESS);
                    assert(shmem[0] == 2);

                    /*
                    # shmdt

                        Detach shared memory from current process:

                            int shmdt(void* shmem);

                        Each process should detach it separatelly before deleting the memory.
                    */
                    {
                        /* Detach from parent. */
                        assert(shmdt(shmem) == 0);
                    }

                    /*
                    # shmctl

                        Controls the shared memory, doing amongst other things its deletion

                            int shmctl(int shm_id, int command, struct shmid_ds *buf);

                        -   shm_id returned by shmget

                        -   command is one of the following:

                            -   `IPC_STAT`: get parameters of memory into buf

                            -   `IPC_SET`:  set parameters of memory to match buf

                            -   `IPC_RMID`: delete memory.

                                It must be detached from all processes, or you get unspecified behaviour.

                        -   buf the following struct:

                                struct shmid_ds {
                                    uid_t shm_perm.uid;
                                    uid_t shm_perm.gid;
                                    mode_t shm_perm.mode;
                                }

                            it can be `NULL` for `PIC_RMID`

                        -   Return: 0 on success, -1 on failure.
                    */
                    {
                        assert(shmctl(shmid, IPC_RMID, NULL) == 0);
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
