#include <gtest/gtest.h>
#include <dxf/dxf.h>
#include <dxf/dxfwriter.h>
#include <usermsg/usermsg.h>

#include <QFile>

class TestUsage : public ::testing::Test {

public:

    TestUsage () {}

    virtual ~TestUsage () {}

    void SetUp(){

    }
    void TearDown(){

    }

};

bool writeSimple (
        const QString &s_output_file, UserMsg &um)
{
    bool b_ret = false;
    for (;;) {
        DxfWriter dwr (s_output_file);

        /* --------------------------------------- */
        if (!dwr.startSecHeader (um)) break;
        if (!dwr.endSecHeader (um)) break;

        /* --------------------------------------- */
        if (!dwr.startSecTables (um)) break; {

            if (!dwr.startTableVport (um)) break; {
                dwr.vpTableAddDefault ();
            }
            if (!dwr.endTableVport (um)) break;

            if (!dwr.startTableLtype (um)) break; {
                dwr.ltyTableAddDefault ();
            }
            if (!dwr.endTableLtype (um)) break;

            if (!dwr.startTableLayer (um)) break;{
                dwr.lyTableAddDefault ();
                dwr.lyTableAdd ("green", ::Dxf::COLOR_GREEN);
                dwr.lyTableAdd ("red", ::Dxf::COLOR_RED);
                dwr.lyTableAdd ("white", ::Dxf::COLOR_WHITE_BLACK);
            }
            if (!dwr.endTableLayer (um)) break;

            if (!dwr.startTableStyle (um)) break; {
                dwr.styleTableAddDefault ();
            }
            if (!dwr.endTableStyle (um)) break;

            if (!dwr.startTableAppId (um)) break; {
                 dwr.appidTableAddDefault ();
            }
            if (!dwr.endTableAppId (um)) break;

            if (!dwr.startTableView (um)) break;
            if (!dwr.endTableView (um)) break;

            if (!dwr.startTableUCS (um)) break;
            if (!dwr.endTableUCS (um)) break;

            if (!dwr.startTableDimStyle (um)) break; {
                dwr.dimstyleTableAddDefault ();
            }
            if (!dwr.endTableDimStyle (um)) break;
        }
        if (!dwr.endSecTables (um)) break;

        /* --------------------------------------- */
        if (!dwr.startSecBlocks (um)) break; {
            dwr.blockAddDefModel ();
            dwr.blockAddDefPaper ();
        }
        if (!dwr.endSecBlocks (um)) break;

        /* --------------------------------------- */
        if (!dwr.startSecEntities (um)) break; {
            if (!dwr.startPolyline ("0", um)) break; {
                dwr.appendVertex (10.0, 10.0, 0.0);
                dwr.appendVertex (100.0, 10.0, 0.0);
            }
            if (!dwr.endPolyline (um)) break;

            dwr.appendText (
                        "green", "bau",
                        15.0, 16.0, 17.0,
                        1.5, 3.1415 * 90 / 180);
            dwr.appendCircle (
                        "red", 17.89,
                        15.0, 16.0, 17.0);
            dwr.appendPoint (
                        "white",
                        15.0, 16.0, 17.0);
        }
        if (!dwr.endSecEntities (um)) break;

        /* --------------------------------------- */

        b_ret = true;
        break;
    }

    return b_ret;
}



TEST_F(TestUsage, write) {
    QString s_output_file = "tmp.dxf";
    UserMsg um;
    EXPECT_TRUE (writeSimple (s_output_file, um));

    QFile f (s_output_file);
    ASSERT_TRUE (f.exists ());

    //f.remove ();
}

