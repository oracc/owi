#include <psd_base.h>
#include <dbi.h>
#include <hash.h>
#include <runexpat.h>
#include <selib.h>

extern char *strdup(const char *);

Hash_table *signmap;
static char *curr_name;
static Dbi_index *dp;

static void
sm_startElement(void *userData, const char *name, const char **atts)
{
  if (!strcmp(name,"sign"))
    curr_name = strdup(attr_by_name(atts,"n"));
  else if (!strcmp(name,"v"))
    {
      XML_Char *v = strdup(attr_by_name(atts,"n"));
      if (!strstr(v,"\xe2\x82\x8a")) /* good enough as a test for sub-+*/
	{
	  if (!hash_find(signmap,(const unsigned char *)v))
	    hash_add(signmap, (const unsigned char *)strdup(v), curr_name);
	}
    }

  charData_discard();
}

static void
sm_endElement(void *userData, const char *name)
{
#if 0
  if (!strcmp(name,"v"))
    {
      XML_Char *v = charData_retrieve();
      if (!strstr(v,"\xe2\x82\x8a")) /* good enough as a test for sub-+*/
	{
	  if (!hash_find(signmap,(const unsigned char *)v))
	    hash_add(signmap, (const unsigned char *)strdup(v), curr_name);
	}
    }
#endif
}

void
signmap_init()
{
  const char *mapfile[2] = 
    { 
      "@@ORACC@@/xml/ogsl/ogsl.xml", 
      NULL 
    };
  signmap = hash_create(8000);
  runexpat(i_list,mapfile,sm_startElement,sm_endElement);
}

static void
savemap(unsigned char *k,void*d)
{
  static char gbuf[PADDED_GRAPHEME_LEN];
  if (strlen((const char *)d) > PADDED_GRAPHEME_LEN-1)
    fprintf(stderr,"setxtx: overlong sign name in savemap: %s\n", (char*)d);
  else
    dbi_add(dp,k,strcpy(gbuf,d),1);
}

void
signmap_term(Dbi_index *dparg)
{
  dp = dparg;
  hash_exec2(signmap,savemap);
}
