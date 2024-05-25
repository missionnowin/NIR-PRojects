/* Written by Miljenko Suljic, m.suljic@cern.ch */

#include <TH2.h>

//_______________________________________________________________________________________________
void dblcol_adr_to_col_row(UShort_t doublecol, UShort_t address, UShort_t &col, UShort_t &row) {
    col = doublecol*2 + (address%4 < 2 ? 1 : 0);
    row = 2*(address/4) + 1-(address%2);
}

//_______________________________________________________________________________________________
UShort_t dblcol_adr_to_col(UShort_t doublecol, UShort_t address) {
    UShort_t col, row;
    dblcol_adr_to_col_row(doublecol, address, col, row);
    return col;
}

//_______________________________________________________________________________________________
UShort_t dblcol_adr_to_row(UShort_t doublecol, UShort_t address) {
    UShort_t col, row;
    dblcol_adr_to_col_row(doublecol, address, col, row);
    return row;
}


//_______________________________________________________________________________________________
void zoom_th2(TH2* h, Int_t offset) {
    Int_t x1 = h->FindFirstBinAbove(0, 1);
    Int_t x2 = h->FindLastBinAbove(0, 1);
    Int_t y1 = h->FindFirstBinAbove(0, 2);
    Int_t y2 = h->FindLastBinAbove(0, 2);
    if( x1 != -1 && x2 != -1 && y1 != -1 && y2 != -1 ) {
        h->GetXaxis()->SetRange(x1-offset, x2+offset);
        h->GetYaxis()->SetRange(y1-offset, y2+offset);
    }

}

void helpers() {
    printf("Helpers loaded.\n");
}
