/**
 * @brief		The application entry point.
 * @file
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <libxml/xmlwriter.h>

#define MY_FILENAME	"./out.xml"
#define MY_ENCODING	"ISO-8859-1"

/**
 * @brief		Tutorial function - Writes an XML file.
 */
static void
fct0(void)
{
	//---Create & configure a writer---//
	xmlTextWriter*	wtr;
	assert(NULL	!= (wtr = xmlNewTextWriterFilename(MY_FILENAME, 0)));
	assert(-1	!= xmlTextWriterSetIndent(wtr, 1));
	assert(-1	!= xmlTextWriterSetIndentString(wtr, BAD_CAST u8"\t"));

	//---Start the document---//
	assert(-1	!= xmlTextWriterStartDocument(wtr, NULL, MY_ENCODING, NULL));

	//---Start the root element---//
	assert(-1	!= xmlTextWriterStartElement(wtr, BAD_CAST u8"root"));

	//---Start the first child element---//
	assert(-1	!= xmlTextWriterStartElement(wtr, BAD_CAST u8"child0"));

	//---Write an attribute---//
	assert(-1	!= xmlTextWriterWriteFormatAttribute(wtr, BAD_CAST u8"attr0", "%s-%u", u8"cédric", 1234));

	//---Write some text---//
	assert(-1	!= xmlTextWriterWriteString(wtr, BAD_CAST u8"hello, world !"));

	//---End the first child element---//
	assert(-1	!= xmlTextWriterEndElement(wtr));

	//---End the root element---//
	assert(-1	!= xmlTextWriterEndElement(wtr));

	//---End the document---//
	assert(-1	!= xmlTextWriterEndDocument(wtr));

	//---Release memory---//
	xmlFreeTextWriter(wtr);
}

/**
 * @brief		Tutorial function - Parses an XML file.
 */
static void
fct1(void)
{
	//---Parse the file---//
	xmlDoc*	doc;
	assert(NULL	!= (doc = xmlReadFile(MY_FILENAME, NULL, XML_PARSE_NOBLANKS)));

	//---Get the root element---//
	xmlNode*	root;
	assert(NULL	!= (root = xmlDocGetRootElement(doc)));
	assert(0	== strcmp((const char*)(root->name), u8"root"));

	//---Get the child---//
	xmlNode*	child0;
	assert(NULL	!= (child0 = xmlFirstElementChild(root)));
	assert(0	== strcmp((const char*)(child0->name), u8"child0"));

	//---Get the attribute---//
	{
		xmlChar*	val;
		assert(NULL	!= (val = xmlGetProp(child0, BAD_CAST u8"attr0")));
		assert(0	== strcmp((const char*)val, u8"cédric-1234"));
		xmlFree(val);
	}

	//---Get the content---//
	{
		xmlChar*	ctnt;
		assert(NULL	!= (ctnt = xmlNodeGetContent(child0)));
		assert(0	== strcmp((const char*)ctnt, u8"hello, world !"));
		xmlFree(ctnt);
	}

	//---Release memory---//
	xmlFreeDoc(doc);
}

/**
 * @brief		The application entry point.
 * @param		[in]	argc	The number of arguments.
 * @param		[in]	argv	The arguments values.
 * @return		Returns EXIT_SUCCESS on success.
 */
extern int
main(int argc, char* argv[])
{
	//---Log---//
	printf("%s started\n", __func__);

	//---Initialize library & check compatibility---//
	LIBXML_TEST_VERSION

	//---Run---//
	fct0();
	fct1();

	//---Cleanup---//
	xmlCleanupParser();

	//---Dump memory to debug for regression tests---//
	xmlMemoryDump();

	//---Return---//
	printf("%s terminated\n", __func__);
	return EXIT_SUCCESS;
}
