clear all

% To było pierwotnie
% size = 3;
size = 3;

fileID = fopen("image.hist","r");
formatSpec = '%f %f';
sizeA = [2 Inf];
A = fscanf(fileID, formatSpec,sizeA);

B = [];
for i=1:width(A)
    B = [B, repmat(A(1,i),1,A(2,i))];
end

imageVar = var(B)

figure;
histogram(B,'BinWidth',size);
hold on;
fclose(fileID);

% ---------------------------------

fileID2 = fopen("image_prediction.hist","r");
formatSpec = '%f %f';
sizeA = [2 Inf];
A = fscanf(fileID2, formatSpec,sizeA);

B = [];
for i=1:width(A)
    B = [B, repmat(A(1,i),1,A(2,i))];
end

imageVar_pred = var(B)

% figure;
histogram(B,'BinWidth',size);
title('Histogramy - boat.pgm');
legend('Dane wejściowe','Dane po predykcji - Mediana L,T,L&T');
set(gcf,'units','points','position',[100,100,500,400])

fclose(fileID2);