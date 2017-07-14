/*
 * This test is loosely based on:
 *
 * http://git.tukaani.org/xz.git
 *     doc/examples_old/xz_pipe_decomp.c
 *
 * https://git.tukaani.org/?p=xz.git;a=blob;f=doc/examples_old/xz_pipe_decomp.c
 */

#include <QDebug>
#include <QFile>

#include <lzma.h>

#include "test_lzma.h"

Test_Lzma::Test_Lzma()
{

}

void Test_Lzma::info(){
    qDebug() << "LZMA Ver." << LZMA_VERSION_STRING;
}


/* read/write buffer sizes */
#define IN_BUF_MAX      (1024 * 32)
#define OUT_BUF_MAX     (1024 * 32)

/* error codes */
#define RET_OK                  0
#define RET_ERROR_INIT          1
#define RET_ERROR_INPUT         2
#define RET_ERROR_OUTPUT        3
#define RET_ERROR_DECOMPRESSION 4


bool Test_Lzma::test(QString in, QString out){
        lzma_stream strm = LZMA_STREAM_INIT; /* alloc and init lzma_stream struct */
        const uint32_t flags = LZMA_TELL_UNSUPPORTED_CHECK | LZMA_CONCATENATED;
        const uint64_t memory_limit = UINT64_MAX; /* no memory limit */
        uint8_t in_buf [IN_BUF_MAX];
        uint8_t out_buf [OUT_BUF_MAX];
        size_t in_len;  /* length of useful data in in_buf */
        size_t out_len; /* length of useful data in out_buf */
        bool in_finished = false;
        bool out_finished = false;
        lzma_action action;
        lzma_ret ret_xz;
        int ret;

        ret = RET_OK;

        /* initialize xz decoder */
        ret_xz = lzma_stream_decoder (&strm, memory_limit, flags);
        if (ret_xz != LZMA_OK) {
                qDebug() <<  "lzma_stream_decoder error: " << ret_xz;
                return false;
        }

        /* Open the inFile and outfile and prepare to read it in chunks */
        QFile inFile(in);
        if (!inFile.open(QIODevice::ReadOnly)){
            qDebug() << "File (In) Open Error";
            return false;
        }

        QFile outFile(out);
        if (!outFile.open(QIODevice::WriteOnly)){
            qDebug() << "File (Out) Open Error";
            return false;
        }


        while ((! in_finished) && (! out_finished)) {
                /* read incoming data */
                in_len = inFile.read(reinterpret_cast<char*>(in_buf), IN_BUF_MAX);

                if (inFile.atEnd()) {
                        in_finished = true;
                }

                strm.next_in = in_buf;
                strm.avail_in = in_len;

                /* if no more data from in_buf, flushes the
                   internal xz buffers and closes the decompressed data
                   with LZMA_FINISH */
                action = in_finished ? LZMA_FINISH : LZMA_RUN;

                /* loop until there's no pending decompressed output */
                do {
                        /* out_buf is clean at this point */
                        strm.next_out = out_buf;
                        strm.avail_out = OUT_BUF_MAX;

                        /* decompress data */
                        ret_xz = lzma_code (&strm, action);

                        if ((ret_xz != LZMA_OK) && (ret_xz != LZMA_STREAM_END)) {
                                fprintf (stderr, "lzma_code error: %d\n", (int) ret_xz);
                                out_finished = true;
                                ret = RET_ERROR_DECOMPRESSION;
                        } else {
                                /* write decompressed data */
                                out_len = OUT_BUF_MAX - strm.avail_out;
                                outFile.write(reinterpret_cast<char*>(out_buf),out_len);
                        }
                } while (strm.avail_out == 0);
        }

        lzma_end (&strm);

        return true;
}

