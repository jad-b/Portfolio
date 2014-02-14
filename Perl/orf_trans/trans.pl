#!/usr/bin/perl -w
#
#  fastaparse.pl fastafile
#
#   @created on 8/31/08 by rdb
#   
#   @modified on 1/31/13 by Jeremy Dobbins-Bucklad for MCBS 913
#   

use warnings;
use strict;

use warnings;
use strict;

my $usageMsg = q(   Usage: ht fastafile
          Extract each sequence from a fastafile into a single string.
          Converts DNA sequences into protein data.
          
          Output is the input sequences converted into their respective proteins.
          Output sent to standard output.);


#+++++++++++++++++++++++ set file name here +++++++++++++++++++++++++++++
&checkUsage();
my $seqFile = $ARGV[ 0 ];   # comment this line if assigning file name above
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

open ( IN, $seqFile )  or die "Unable to open: ".$seqFile ;


#--------Read in all the fasta files--------#
# first line better be a sequence header
my $header = <IN>;	#Read from stdin
if ( substr( $header, 0, 1 ) ne '>' )#if there's not a '>', print error	
{
   print "********* ERROR ********* Expecting header, got:\n $header";
   print " is this a fasta file??? ";
   exit;
}
my @headers,my @sequences;
my $index = 0;
while ( $header )	#While we're reading in headers
{
   $headers[$index] = $header;	#Save header
   my $seq = ""; 	#intialize string
   my $inLine = <IN>;	#grab first line

   # read in all input lines of bases
	#while we're reading lines & it's not a header
   while ( $inLine && substr( $inLine, 0, 1 ) ne '>' )	
   {
      chomp( $inLine );     # remove line feed with chomp!
      $seq = $seq . $inLine;	#String concat? Yep. String concat.
      $inLine = <IN>;	#Read a new line
   }
	$sequences[$index++] = $seq;	#save sequence
   $header = $inLine;    # last line read is either next header or null
}
#-----done reading-----#

my %aminoAcids = ( 	"TTT" => "F",
			"TTC" => "F",
			"TTA" => "L",
			"TTG" => "L",
			"CTT" => "L",
			"CTC" => "L",
			"CTA" => "L",		
			"CTG" => "L",
			"ATT" => "I",
			"ATC" => "I",
			"ATA" => "I",
			"ATG" => "M",
			"GTT" => "V",
			"GTC" => "V",
			"GTA" => "V",
			"GTG" => "V",
			"TCT" => "S",
			"TCC" => "S",
			"TCA" => "S",
			"TCG" => "S",
			"CCT" => "P",
			"CCC" => "P",
			"CCA" => "P",
			"CCG" => "P",
			"ACT" => "T",	
			"ACC" => "T",
			"ACA" => "T",
			"ACG" => "T",
			"GCT" => "A",
			"GCC" => "A",
			"GCA" => "A", 
			"GCG" => "A",
			"TAT" => "Y",
			"TAC" => "Y",
			"TAA" => "*",
			"TAG" => "*",
			"CAT" => "H",
			"CAC" => "H",
			"CAA" => "Q",
			"CAG" => "Q",
			"AAT" => "N",
			"AAC" => "N",
			"AAA" => "K",
			"AAG" => "K",
			"GAT" => "D",
			"GAC" => "D",
			"GAA" => "E",
			"GAG" => "E",
			"TGT" => "C",
			"TGC" => "C",
			"TGA" => "*",
			"TGG" => "W",
			"CGT" => "R",
			"CGC" => "R",
			"CGA" => "R",
			"CGG" => "R",
			"AGT" => "S",
			"AGC" => "S",
			"AGA" => "R",
			"AGG" => "R",
			"GGT" => "G",
			"GGC" => "G",
			"GGA" => "G",
			"GGG" => "G",
		);
			

#my @codons = keys(%aminoAcids);
#print 'foreach my $codon( keys(%aminoAcids))' . "\n";
#foreach my $codon( keys(%aminoAcids )){
#	print "$codon: $aminoAcids{ $codon }\n";
#}

my @proteins;
my $codon = "[ACTG]{3}";
#loop through each sequences
for( my $i = 0; $i < @sequences; $i++ ){
	my $seq = $sequences[$i];
	my $pep = "";
	my $match = $seq =~ m/$codon/g;
	while($match){
		#print "($& / $aminoAcids{$&})\n";
		$pep = $pep . $aminoAcids{ $& };
		$match = $seq =~ m/$codon/g;
	}
	$proteins[$i] = $pep;
}

for(my $i = 0; $i < @proteins; $i++ ){
	print "$headers[$i]$proteins[$i]\n\n";
}

#++++++++++++++++++ subroutine checkUsage() ++++++++++++++++++++++++++++++++
sub checkUsage()
{
   if ( @ARGV == 0 || $ARGV[0] eq "-h" )
   {
      print STDERR "$usageMsg\n";
      exit;
   }
}

