close all;
addpath('material_P5/ViolaJones', 'material_P5/ViolaJones/SubFunctions'); % Adding to the path the detector.

outSize = [20, 20]; % Defining size of the model.

if ~exist('numFeatures','var'),
    numFeatures=3;
end

[X,Y] = getDataBase(outSize,15); % Creating the database and retrieving the model.

% Get the average face as model
model=uint8(round(reshape(mean(X(Y==1,:),1),outSize)));

for f=1:numFeatures,
    [rectPos,rectNeg,rectPosS,rectNegS]=selectFeature(model,outSize);
    selFeatures=[selFeatures;rectPos rectNeg];
end

figure,
    showFeatures(model,selFeatures);
figure,
    showIntegralImage(model);
    
figure,
    ConvertHaarcasadeXMLOpenCV('material_P5/ViolaJones/HaarCascades/haarcascade_frontalface_alt.xml');
    % Detect Faces
    Options.Resize=false;
    ObjectDetection('face1.jpg','material_P5/ViolaJones/HaarCascades/haarcascade_frontalface_alt.mat',Options);

function [rectPos,rectNeg,rectPosS,rectNegS]=selectFeature(model,outSize)
    x = [3 7 14 4]; % Extracted from the XML file, from the <rects> attribute.
    y = [3 9 14 2];
    mSize=size(model);
    
    % Get the feature
    rectPos=round([x(1) y(1) x(2)-x(1)+1 y(2)-y(1)+1]);
    rectNeg=round([x(2)+1 y(1) rectPos(3) rectPos(4)]);
    
    % Correct the feature
    if rectNeg(2)+rectNeg(4)-1>mSize(1),
        overLength=(rectNeg(2)+rectNeg(4)-1)-mSize(1);
        rectPos(2)=rectPos(2)+overLength-1;
        rectPos(4)=rectPos(4)-overLength;
        rectNeg(4)=rectNeg(4)-overLength;
    end
    if rectNeg(1)+rectNeg(3)-1>mSize(2),
        overLength=(rectNeg(1)+rectNeg(3)-1)-mSize(2);
        rectPos(1)=rectPos(1)+overLength-1;
        rectPos(3)=rectPos(3)-overLength;
        rectNeg(3)=rectNeg(3)-overLength;
    end
    

    % Reescale the feature
    s=outSize./mSize;    
    x=x*s(2);
    y=y*s(1);
    rectPosS=round([x(1) y(1) x(2)-x(1)+1 y(2)-y(1)+1]);
    rectNegS=round([x(2)+1 y(1) rectPosS(3) rectPosS(4)]);        
    
    % Correct the feature
    if rectNegS(2)+rectNegS(4)-1>outSize(1),
        overLength=(rectNegS(2)+rectNegS(4)-1)-outSize(1);
        rectPosS(2)=rectPosS(2)+overLength-1;
        rectPosS(4)=rectPosS(4)-overLength;
        rectNegS(4)=rectNegS(4)-overLength;
    end
    if rectNegS(1)+rectNegS(3)-1>outSize(2),
        overLength=(rectNegS(1)+rectNegS(3)-1)-outSize(2);
        rectPosS(1)=rectPosS(1)+overLength-1;
        rectPosS(3)=rectPosS(3)-overLength;
        rectNegS(3)=rectNegS(3)-overLength;
    end
end

function showFeatures(model,selFeatures)
    %Show the model        
    imshow(model);title('Selected features');
    hold on;
    for i=1:size(selFeatures,1),
        rectPos=selFeatures(i,1:4);
        rectNeg=selFeatures(i,5:8);
        % Show feature
        rectangle('position',rectPos,'facecolor','w');
        rectangle('position',rectNeg,'facecolor','k');
    end
end

function showIntegralImage(image)
    defaultoptions.Resize=false;			
    intImageStruct=GetIntegralImages(image,defaultoptions);
    imagesc(intImageStruct.ii);colormap(jet);
end