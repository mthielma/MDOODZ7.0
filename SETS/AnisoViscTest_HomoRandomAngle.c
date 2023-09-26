#include "math.h"
#include "mdoodz.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

int SetPhase(MdoodzInput *input, Coordinates coordinates) {

  int nellipses = 0;

  // (for 299 setup)
  double Xshift[299]  = { -0.22816 , -0.021336 , 0.05523 , -0.32056 , 0.25487 , -0.078159 , 0.19636 , 0.10404 , 0.25895 , -0.022912 , -0.28754 , -0.38468 , -0.089949 , -0.0050744 , 0.17039 , -0.318 , 0.40806 , 0.19729 , -0.47074 , -0.38096 , 0.47563 , -0.42267 , -0.36596 , 0.12273 , -0.092511 , -0.40519 , -0.084045 , 0.10114 , -0.3926 , -0.029798 , -0.2662 , -0.19559 , -0.075464 , 0.07131 , -0.48309 , -0.019021 , 0.49423 , 0.00028556 , 0.08106 , 0.19416 , 0.00084054 , 0.53115 , 0.069583 , 0.30878 , -0.16643 , -0.026291 , 0.38379 , 0.50059 , -0.53594 , -0.28638 , 0.37212 , -0.44905 , 0.44363 , 0.01414 , -0.31281 , 0.43897 , 0.090365 , -0.51925 , 0.17622 , 0.35899 , -0.388 , -0.036146 , 0.53654 , -0.1379 , 0.46033 , -0.36426 , -0.51956 , -0.084741 , 0.20375 , -0.20879 , -0.13447 , 0.34352 , -0.32432 , -0.20247 , -0.45219 , -0.3114 , 0.24505 , -0.083951 , 0.23035 , -0.30295 , 0.30972 , 0.028167 , -0.44292 , 0.41391 , -0.22493 , -0.12975 , -0.163 , -0.53987 , -0.21171 , -0.54145 , 0.12609 , -0.080698 , 0.040559 , -0.040591 , 0.41627 , -0.47606 , -0.25297 , 0.51085 , -0.20487 , 0.27565 , -0.42918 , -0.29596 , -0.24222 , 0.31079 , 0.052846 , -0.013232 , -0.10747 , 0.21718 , 0.49894 , -0.41927 , -0.36252 , 0.29682 , 0.48155 , 0.14915 , -0.098248 , -0.12913 , -0.32764 , 0.010045 , 0.24628 , -0.53413 , 0.065074 , 0.039831 , 0.31714 , 0.093487 , -0.22003 , 0.34886 , 0.37217 , 0.10217 , -0.53436 , -0.049081 , 0.52527 , 0.068685 , 0.27133 , 0.0031221 , 0.18593 , -0.45724 , -0.16345 , 0.39594 , -0.015962 , -0.069537 , 0.36635 , 0.52031 , -0.37068 , 0.32639 , 0.36991 , -0.3419 , -0.093731 , 0.3124 , -0.23413 , -0.28888 , -0.025687 , -0.27212 , 0.37024 , 0.21112 , -0.118 , -0.37629 , -0.41248 , 0.048335 , -0.41036 , -0.2483 , -0.14721 , -0.10204 , 0.36277 , -0.27307 , 0.27017 , -0.16687 , 0.079883 , 0.42454 , 0.44547 , -0.25542 , 0.21606 , 0.047524 , -0.26081 , -0.45067 , 0.28547 , 0.4304 , 0.27773 , 0.25735 , -0.057085 , -0.17188 , -0.059101 , 0.3709 , -0.54234 , -0.43161 , 0.035947 , 0.39347 , -0.052967 , 0.11991 , 0.28647 , 0.19851 , 0.44191 , -0.25738 , 0.097025 , 0.055415 , 0.45101 , -0.18302 , -0.4336 , -0.40715 , -0.26009 , 0.44376 , 0.22898 , 0.16317 , -0.049781 , -0.39171 , -0.45436 , 0.0063516 , -0.18887 , -0.44237 , -0.16966 , -0.16166 , 0.30487 , -0.26893 , 0.52784 , -0.4828 , -0.2379 , 0.38542 , 0.34065 , -0.13584 , -0.39507 , 0.292 , -0.064576 , 0.44992 , 0.38687 , 0.38762 , -0.13723 , 0.24304 , -0.25919 , -0.23592 , -0.16201 , -0.10797 , -0.064879 , 0.29997 , 0.35496 , 0.040786 , -0.35007 , 0.38789 , -0.15498 , -0.15759 , 0.07224 , -0.36945 , 0.18746 , -0.34249 , -0.36879 , -0.20154 , 0.061779 , -0.073078 , 0.19187 , -0.19955 , 0.37717 , -0.18949 , -0.54227 , 0.54145 , 0.2583 , -0.31814 , -0.21199 , 0.37992 , 0.15956 , -0.10309 , 0.2234 , 0.32783 , 0.3771 , -0.31839 , 0.17589 , -0.43926 , -0.098158 , -0.089941 , 0.020064 , 0.46082 , -0.27499 , 0.03183 , -0.47407 , 0.46537 , -0.003658 , 0.51691 , -0.50577 , -0.46885 , -0.49941 , 0.46406 , 0.48075 , -0.46346 , 0.48044 , 0.46013 , 0.45855 , 0.52394 , -0.48915 , -0.50106 , -0.51845 , 0.46587 , 0.46564 , -0.47473 , -0.47969 , 0.45766 , -0.47216 , 0.5172 , 0.45773 , -0.45855 , -0.53918 , 0.52593 , -0.53463 };
  double Zshift[299]  = { 0.5415 , -0.026175 , 0.38234 , -0.37879 , -0.031663 , -0.50704 , 0.24111 , 0.090023 , -0.091293 , -0.074906 , -0.2646 , 0.16727 , 0.064955 , -0.11888 , 0.37096 , -0.54272 , 0.34296 , 0.40407 , 0.51143 , -0.22603 , 0.22583 , -0.37372 , 0.42521 , -0.33813 , 0.28935 , 0.47852 , 0.45326 , -0.26711 , 0.24635 , -0.1562 , 0.43203 , 0.25527 , -0.45837 , 0.3046 , 0.24536 , 0.5239 , -0.21266 , 0.059282 , -0.3272 , 0.4344 , -0.039987 , 0.37979 , -0.08379 , 0.18575 , -0.27354 , 0.3139 , 0.12818 , -0.3746 , 0.18782 , 0.3387 , 0.28979 , 0.29479 , -0.38265 , 0.43713 , 0.50258 , 0.52507 , 0.37962 , 0.43927 , -0.3569 , -0.39338 , 0.33268 , -0.34848 , 0.1981 , -0.32482 , 0.40577 , 0.51918 , -0.052263 , -0.12362 , -0.17924 , -0.47367 , 0.43365 , -0.50578 , 0.40676 , 0.53135 , -0.2853 , -0.082201 , 0.51513 , 0.22755 , -0.12373 , 0.53182 , -0.36663 , 0.30579 , -0.099646 , -0.093709 , 0.1277 , -0.0054239 , 0.29654 , 0.37043 , 0.166 , 0.3242 , -0.52519 , -0.035496 , 0.17399 , -0.23772 , 0.01141 , -0.54485 , -0.53264 , 0.17363 , -0.10154 , 0.29367 , -0.0056675 , 0.18975 , -0.31213 , -0.46908 , -0.37156 , 0.18793 , -0.32041 , 0.25593 , -0.16684 , 0.20145 , 0.20993 , 0.11047 , -0.30298 , 0.54115 , -0.27183 , -0.47836 , -0.14523 , 0.51425 , 0.21178 , -0.50743 , -0.54139 , 0.14244 , -0.53099 , -0.24178 , -0.3699 , -0.24031 , 0.54045 , 0.43709 , 0.27353 , 0.039606 , 0.072539 , -0.46702 , 0.0050052 , 0.10811 , -0.48881 , -0.32163 , -0.0020008 , -0.16712 , -0.47333 , -0.0052957 , -0.43963 , -0.46954 , -0.035304 , 0.36634 , 0.40783 , -0.28039 , -0.36128 , 0.053035 , 0.27931 , 0.090446 , 0.46951 , 0.50602 , 0.052007 , -0.25658 , 0.050455 , 0.13301 , -0.27248 , -0.27492 , 0.035256 , -0.43586 , 0.18338 , -0.5343 , 0.17652 , 0.29816 , -0.17234 , 0.055155 , -0.0047934 , -0.037906 , -0.32944 , 0.38764 , -0.3552 , 0.3356 , -0.19353 , 0.24259 , -0.32704 , 0.078286 , 0.37657 , 0.05733 , 0.14018 , -0.43498 , 0.51929 , -0.017455 , -0.086105 , 0.094388 , 0.52401 , -0.54389 , -0.54091 , -0.41362 , -0.43836 , 0.015585 , 0.14916 , -0.47846 , -0.38079 , -0.22913 , 0.041096 , -0.20817 , 0.39094 , 0.5437 , 0.0048242 , -0.43728 , -0.5396 , -0.069328 , -0.1615 , -0.46176 , -0.14909 , 0.28491 , 0.41844 , -0.47852 , 0.36699 , 0.477 , 0.4616 , -0.11209 , 0.023602 , 0.1294 , 0.043565 , -0.35396 , 0.002009 , -0.14754 , -0.52797 , -0.25148 , -0.22665 , -0.35621 , 0.16845 , -0.21548 , -0.21882 , -0.24656 , -0.38865 , 0.45176 , -0.18102 , 0.53679 , -0.28183 , 0.52386 , 0.4389 , 0.47522 , -0.34161 , 0.48019 , -0.4894 , -0.34372 , -0.16902 , -0.39673 , 0.48618 , -0.19908 , 0.38465 , 0.19825 , 0.24221 , 0.34745 , 0.54175 , -0.28974 , -0.25584 , 0.047639 , -0.22256 , 0.44844 , -0.39822 , 0.35743 , -0.14659 , -0.077251 , 0.25557 , -0.40132 , 0.30568 , -0.11616 , 0.24221 , 0.065132 , 0.16769 , -0.19437 , -0.056612 , 0.37653 , -0.41642 , -0.27579 , -0.3475 , 0.25428 , -0.40994 , -0.53469 , -0.30806 , 0.24536 , -0.21266 , 0.37979 , -0.3746 , 0.18782 , 0.43927 , 0.1981 , -0.052263 , 0.37043 , 0.3242 , -0.54485 , 0.17363 , -0.16684 , -0.30298 , -0.50743 , 0.27353 , 0.072539 , -0.46954 , -0.086105 , 0.023602 , 0.1294 , -0.22256 , 0.44844 , -0.27579 , -0.40994 , -0.53469 };
  double Majaxis[299] = { 0.020004 , 0.02004 , 0.020062 , 0.02011 , 0.020123 , 0.020139 , 0.020181 , 0.020182 , 0.02026 , 0.020279 , 0.020296 , 0.020363 , 0.020363 , 0.020375 , 0.020402 , 0.020422 , 0.020423 , 0.020437 , 0.02046 , 0.020466 , 0.020469 , 0.020523 , 0.020523 , 0.020526 , 0.020548 , 0.020586 , 0.020612 , 0.020696 , 0.020771 , 0.020806 , 0.020844 , 0.020865 , 0.020978 , 0.021012 , 0.021104 , 0.021143 , 0.021148 , 0.02121 , 0.021257 , 0.021287 , 0.021329 , 0.021394 , 0.021405 , 0.021414 , 0.021479 , 0.021621 , 0.021632 , 0.021655 , 0.021672 , 0.021705 , 0.021718 , 0.021849 , 0.02188 , 0.021911 , 0.021912 , 0.022019 , 0.022112 , 0.022149 , 0.022181 , 0.022192 , 0.022249 , 0.022271 , 0.022402 , 0.022414 , 0.022494 , 0.022507 , 0.022762 , 0.022839 , 0.022917 , 0.022925 , 0.022981 , 0.022983 , 0.023031 , 0.02304 , 0.023091 , 0.023163 , 0.023312 , 0.023338 , 0.023453 , 0.023519 , 0.023569 , 0.023595 , 0.023677 , 0.02368 , 0.023704 , 0.023793 , 0.023798 , 0.023855 , 0.023909 , 0.02392 , 0.023965 , 0.023975 , 0.024004 , 0.024045 , 0.024291 , 0.024353 , 0.024388 , 0.024492 , 0.024604 , 0.024626 , 0.024644 , 0.024752 , 0.02477 , 0.024776 , 0.024881 , 0.024971 , 0.025214 , 0.025216 , 0.025264 , 0.025365 , 0.02539 , 0.025435 , 0.025443 , 0.025617 , 0.025749 , 0.025759 , 0.025759 , 0.02576 , 0.025769 , 0.025815 , 0.025948 , 0.026073 , 0.026118 , 0.026124 , 0.026274 , 0.026405 , 0.026577 , 0.026608 , 0.026732 , 0.026777 , 0.026902 , 0.026943 , 0.026962 , 0.027083 , 0.027125 , 0.027125 , 0.027209 , 0.027313 , 0.027426 , 0.027528 , 0.027584 , 0.027658 , 0.02772 , 0.02776 , 0.027777 , 0.027796 , 0.027838 , 0.027882 , 0.027914 , 0.027935 , 0.028 , 0.028058 , 0.02836 , 0.028375 , 0.028442 , 0.0285 , 0.028504 , 0.028511 , 0.028559 , 0.028733 , 0.028799 , 0.028827 , 0.029037 , 0.029057 , 0.029218 , 0.02924 , 0.029269 , 0.02933 , 0.02935 , 0.029397 , 0.029459 , 0.029526 , 0.029534 , 0.029655 , 0.029803 , 0.029817 , 0.029966 , 0.030027 , 0.030029 , 0.030087 , 0.030087 , 0.030147 , 0.030235 , 0.030247 , 0.030314 , 0.030408 , 0.030571 , 0.030698 , 0.030702 , 0.030719 , 0.030815 , 0.030821 , 0.030984 , 0.031028 , 0.031106 , 0.031114 , 0.031309 , 0.031337 , 0.031502 , 0.031505 , 0.031629 , 0.031913 , 0.032007 , 0.032405 , 0.032518 , 0.032618 , 0.032664 , 0.03268 , 0.032684 , 0.033117 , 0.033188 , 0.033196 , 0.033267 , 0.03352 , 0.033834 , 0.033843 , 0.034007 , 0.034245 , 0.03437 , 0.034668 , 0.03473 , 0.034838 , 0.035036 , 0.035053 , 0.035149 , 0.035409 , 0.03557 , 0.03572 , 0.035747 , 0.0358 , 0.035874 , 0.036028 , 0.036202 , 0.036219 , 0.036401 , 0.036418 , 0.036456 , 0.036511 , 0.03658 , 0.036974 , 0.037067 , 0.037142 , 0.037223 , 0.03731 , 0.037346 , 0.037352 , 0.037377 , 0.037485 , 0.037835 , 0.038909 , 0.039492 , 0.039608 , 0.039689 , 0.039796 , 0.039898 , 0.039994 , 0.040015 , 0.040017 , 0.040172 , 0.040309 , 0.040405 , 0.040516 , 0.041238 , 0.041243 , 0.041777 , 0.042256 , 0.042554 , 0.042737 , 0.042815 , 0.042964 , 0.043061 , 0.043634 , 0.043867 , 0.021104 , 0.021148 , 0.021394 , 0.021655 , 0.021672 , 0.022149 , 0.022402 , 0.022762 , 0.023855 , 0.02392 , 0.024353 , 0.024492 , 0.025264 , 0.025443 , 0.025815 , 0.026732 , 0.026902 , 0.027658 , 0.030235 , 0.033267 , 0.03352 , 0.039492 , 0.039608 , 0.042737 , 0.043061 , 0.043634 };
  double Minaxis[299] = { 0.014327 , 0.0099816 , 0.0079475 , 0.0067382 , 0.0092416 , 0.0054686 , 0.0079646 , 0.01336 , 0.012604 , 0.013941 , 0.015507 , 0.006454 , 0.0055965 , 0.010408 , 0.013413 , 0.0097163 , 0.015056 , 0.0061028 , 0.0077156 , 0.0051759 , 0.017189 , 0.0052982 , 0.0096657 , 0.01076 , 0.012129 , 0.012807 , 0.0076778 , 0.006741 , 0.0060004 , 0.0056357 , 0.0053628 , 0.016735 , 0.0052267 , 0.0057199 , 0.0083263 , 0.0094517 , 0.012813 , 0.01103 , 0.0098089 , 0.013574 , 0.006371 , 0.012738 , 0.0073692 , 0.013902 , 0.011126 , 0.0098853 , 0.0080003 , 0.0064415 , 0.0066103 , 0.012389 , 0.0060653 , 0.0087545 , 0.010981 , 0.0092382 , 0.015435 , 0.0096992 , 0.011574 , 0.0080925 , 0.011675 , 0.012981 , 0.015948 , 0.015128 , 0.010294 , 0.0080096 , 0.0051034 , 0.010367 , 0.011007 , 0.010025 , 0.005869 , 0.0055645 , 0.0075996 , 0.0079119 , 0.0055819 , 0.0063155 , 0.0088309 , 0.01453 , 0.0050177 , 0.0053662 , 0.010173 , 0.0082155 , 0.0074167 , 0.006434 , 0.015945 , 0.0077343 , 0.0095707 , 0.016882 , 0.013134 , 0.0059642 , 0.0065564 , 0.015614 , 0.017264 , 0.0075763 , 0.006793 , 0.0051688 , 0.01707 , 0.006315 , 0.010919 , 0.0079502 , 0.0096913 , 0.0082356 , 0.0092863 , 0.0052858 , 0.016991 , 0.011849 , 0.0063774 , 0.010478 , 0.012739 , 0.0069143 , 0.01976 , 0.0086271 , 0.009269 , 0.0091104 , 0.0062468 , 0.01799 , 0.012409 , 0.0053492 , 0.0077024 , 0.0050801 , 0.012564 , 0.0075616 , 0.016538 , 0.0069052 , 0.014742 , 0.0055335 , 0.010662 , 0.0087099 , 0.0092536 , 0.010254 , 0.010465 , 0.0065039 , 0.0055155 , 0.019832 , 0.0089958 , 0.0098236 , 0.018973 , 0.007204 , 0.010104 , 0.01323 , 0.014672 , 0.010585 , 0.0058373 , 0.011372 , 0.013203 , 0.0099765 , 0.0070372 , 0.010354 , 0.0055951 , 0.0060131 , 0.013103 , 0.0079449 , 0.0051299 , 0.005036 , 0.010246 , 0.012704 , 0.0057771 , 0.014115 , 0.014807 , 0.0052778 , 0.0084248 , 0.0096462 , 0.0055434 , 0.0095333 , 0.011269 , 0.01221 , 0.012258 , 0.0067901 , 0.006454 , 0.012845 , 0.014736 , 0.010879 , 0.0083323 , 0.0077235 , 0.0051711 , 0.0069054 , 0.017363 , 0.014372 , 0.0072299 , 0.0063376 , 0.010933 , 0.018564 , 0.0061667 , 0.012848 , 0.0064541 , 0.0058952 , 0.0051857 , 0.0072317 , 0.0078115 , 0.0099858 , 0.010605 , 0.013646 , 0.014084 , 0.0094785 , 0.012782 , 0.010161 , 0.007457 , 0.0051096 , 0.0067752 , 0.0070392 , 0.0055331 , 0.013437 , 0.013798 , 0.0061589 , 0.0051074 , 0.015242 , 0.0051894 , 0.0077062 , 0.010107 , 0.010847 , 0.013242 , 0.0052751 , 0.010423 , 0.0070397 , 0.017173 , 0.0094386 , 0.0074332 , 0.0064722 , 0.0092312 , 0.0059999 , 0.0067572 , 0.010947 , 0.008076 , 0.0054722 , 0.0081541 , 0.0082725 , 0.01725 , 0.0089949 , 0.011478 , 0.017171 , 0.0071159 , 0.006895 , 0.011438 , 0.0068836 , 0.008132 , 0.01367 , 0.0088901 , 0.0059138 , 0.0081291 , 0.0059966 , 0.0086854 , 0.013832 , 0.0068204 , 0.005614 , 0.0096036 , 0.014077 , 0.010208 , 0.0060625 , 0.0052894 , 0.011616 , 0.0050841 , 0.0068374 , 0.0096471 , 0.012576 , 0.016383 , 0.0090394 , 0.0075459 , 0.0057784 , 0.0060681 , 0.013247 , 0.0057273 , 0.0099803 , 0.0070866 , 0.0066253 , 0.007665 , 0.0064052 , 0.010079 , 0.0076156 , 0.0070544 , 0.0063735 , 0.0060472 , 0.0063675 , 0.0062031 , 0.0060378 , 0.0056123 , 0.0083263 , 0.012813 , 0.012738 , 0.0064415 , 0.0066103 , 0.0080925 , 0.010294 , 0.011007 , 0.0059642 , 0.015614 , 0.006315 , 0.0079502 , 0.01976 , 0.0062468 , 0.0075616 , 0.010465 , 0.0055155 , 0.011372 , 0.0064541 , 0.017173 , 0.0094386 , 0.0096471 , 0.012576 , 0.0063735 , 0.0062031 , 0.0060378 };
  double Angle[299]   = { 1.4558 , 1.0249 , 0.91246 , 3.7799 , 1.4959 , 1.7974 , 5.3369 , 5.7376 , 3.5275 , 2.1432 , 3.5593 , 4.3224 , 2.7564 , 1.51 , 4.5466 , 3.919 , 5.4015 , 0.30619 , 0.67212 , 3.5822 , 6.238 , 5.3461 , 5.0576 , 5.0017 , 2.834 , 6.059 , 2.9888 , 3.6527 , 1.3913 , 1.8141 , 4.7455 , 1.4383 , 1.1027 , 1.1936 , 0.59347 , 1.7009 , 3.6973 , 4.8118 , 1.848 , 2.8246 , 1.5613 , 5.2432 , 5.4165 , 5.8815 , 5.5182 , 5.4343 , 2.1553 , 3.0717 , 6.1326 , 3.7169 , 4.8459 , 1.3129 , 0.15237 , 5.8569 , 5.9889 , 0.86512 , 1.9941 , 2.5237 , 5.433 , 0.58891 , 1.7834 , 1.4294 , 4.8015 , 2.0355 , 1.9812 , 0.89478 , 4.4992 , 1.1769 , 4.2821 , 2.4354 , 4.3865 , 2.0177 , 0.76227 , 4.8369 , 2.8215 , 1.646 , 4.3235 , 4.5098 , 2.9366 , 5.7934 , 4.8433 , 0.20172 , 5.7323 , 3.9258 , 0.23259 , 1.5851 , 5.3528 , 5.6937 , 3.1197 , 4.6992 , 1.5269 , 2.9197 , 5.9799 , 3.9698 , 5.1291 , 0.46843 , 0.32144 , 1.3667 , 3.6631 , 4.3596 , 5.3843 , 5.0461 , 2.8384 , 0.4362 , 4.9122 , 0.91605 , 2.291 , 2.334 , 3.6956 , 3.0292 , 1.1774 , 0.82064 , 1.6694 , 3.2481 , 4.5823 , 2.4318 , 4.2287 , 4.6383 , 4.3096 , 6.0267 , 4.974 , 2.5711 , 5.7808 , 0.86595 , 1.9546 , 1.169 , 0.94583 , 1.6645 , 4.3546 , 4.9469 , 4.3364 , 2.9925 , 0.19103 , 1.8663 , 1.8633 , 3.596 , 1.4591 , 1.9571 , 4.8912 , 6.009 , 4.9117 , 1.4427 , 1.1956 , 3.8217 , 1.4041 , 0.48615 , 5.4622 , 2.4336 , 4.6307 , 1.4259 , 2.5079 , 4.2249 , 0.23295 , 4.5866 , 1.6253 , 3.0094 , 5.5111 , 2.2686 , 4.7023 , 2.9195 , 5.0689 , 5.6642 , 4.5094 , 4.5253 , 1.6656 , 4.3838 , 1.1062 , 6.1138 , 0.32075 , 3.4346 , 4.1934 , 6.0929 , 2.803 , 1.7798 , 1.4638 , 1.1769 , 1.6757 , 3.5648 , 5.805 , 1.7655 , 1.869 , 3.4948 , 5.0538 , 0.5722 , 5.2496 , 0.74496 , 0.93514 , 3.845 , 4.0066 , 1.4639 , 0.98186 , 1.6919 , 0.41886 , 5.0204 , 4.4884 , 1.6724 , 2.3402 , 4.468 , 5.6256 , 5.7988 , 4.1419 , 4.5061 , 2.1176 , 6.0354 , 5.7664 , 3.1422 , 4.2172 , 5.2365 , 5.3768 , 1.6359 , 0.86165 , 4.5322 , 4.5114 , 4.4432 , 4.5294 , 5.1042 , 3.9791 , 1.1958 , 1.8184 , 4.6404 , 1.1193 , 2.8933 , 1.0764 , 2.3314 , 4.668 , 5.0065 , 2.2973 , 5.637 , 1.2619 , 2.4728 , 4.9948 , 2.4295 , 0.80222 , 3.4089 , 1.3484 , 1.6781 , 5.9017 , 2.6379 , 2.663 , 5.0669 , 1.9895 , 3.4627 , 2.2352 , 0.15207 , 0.62638 , 6.1007 , 1.1807 , 5.8529 , 4.8815 , 1.5408 , 1.4216 , 4.0129 , 3.5676 , 0.60916 , 0.28774 , 3.7289 , 5.2765 , 1.9752 , 4.8562 , 2.3279 , 5.9472 , 4.7341 , 0.67569 , 2.1298 , 6.1253 , 1.1864 , 5.4152 , 0.9864 , 0.21133 , 0.53214 , 2.5471 , 1.9962 , 1.5181 , 0.59347 , 3.6973 , 5.2432 , 3.0717 , 6.1326 , 2.5237 , 4.8015 , 4.4992 , 5.6937 , 4.6992 , 0.46843 , 1.3667 , 3.6956 , 1.6694 , 6.0267 , 4.3546 , 4.3364 , 1.4427 , 5.0538 , 4.5114 , 4.4432 , 1.4216 , 4.0129 , 0.9864 , 2.5471 , 1.9962 };

  // (for 5 setup)
  //double Xshift[5]  = { -0.22816 , -0.021336 , 0.05523 , -0.32056 , 0.25487 };
  //double Zshift[5]  = { 0.5415 , -0.026175 , 0.38234 , -0.37879 , -0.031663 };
  //double Majaxis[5] = { 0.020004 , 0.02004 , 0.020062 , 0.02011 , 0.020123 };
  //double Minaxis[5] = { 0.014327 , 0.0099816 , 0.0079475 , 0.0067382 , 0.0092416 };
  //double Angle[5]   = { 1.4558 , 1.0249 , 0.91246 , 3.7799 , 1.4959 };

  // scaling geometry values
  int i;
  for (i = 0; i < nellipses; ++i) {
    Xshift[i]  = Xshift[i]  / input->scaling.L;
    Zshift[i]  = Zshift[i]  / input->scaling.L;
    Majaxis[i] = Majaxis[i] / input->scaling.L;
    Minaxis[i] = Minaxis[i] / input->scaling.L;
    // Angle doesn't need scaling (in radians btw)
  }

  bool isInsideSomeEllipse = false;
  bool isInsideThisEllipse = false;
  for (i = 0; i < nellipses; ++i) {
    isInsideThisEllipse = ((coordinates.x - Xshift[i])*cos(Angle[i]) + (coordinates.z - Zshift[i])*sin(Angle[i]))*((coordinates.x - Xshift[i])*cos(Angle[i]) + (coordinates.z - Zshift[i])*sin(Angle[i]))/(Majaxis[i] * Majaxis[i]) + (-(coordinates.z - Zshift[i])*cos(Angle[i]) + (coordinates.x - Xshift[i])*sin(Angle[i]))*(-(coordinates.z - Zshift[i])*cos(Angle[i]) + (coordinates.x - Xshift[i])*sin(Angle[i]))/ (Minaxis[i] * Minaxis[i]) < 1; // rotated ellipse
    // reminder ellipse function: inside = [(x-x0)*cos(phi)+(z-z0)*sin(phi)]^2/majaxis^2 + [(x-x0)*sin(phi)-(z-z0)*cos(phi)]^2/minaxis^2 < 1
    if (isInsideThisEllipse) {
      isInsideSomeEllipse = true;
    }
  }
  if (isInsideSomeEllipse) {
    return 1;
  } else {
    return 0;
  }
}

double SetDensity(MdoodzInput *input, Coordinates coordinates, int phase) {
  const double T_init = (zeroC) / input->scaling.T;
  if (1 == 0) {
    return input->materials.rho[phase] * (1 - input->materials.alp[phase] * (T_init - input->materials.T0[phase]));
  } else {
    return input->materials.rho[phase];
  }
}

double SetAnisoAngle(MdoodzInput *input, Coordinates coordinates, int phase) {
  const double radius = input->model.user1 / input->scaling.L;

  int nellipses = 0;

  // (for 299 setup)
  double Xshift[299]  = { -0.22816 , -0.021336 , 0.05523 , -0.32056 , 0.25487 , -0.078159 , 0.19636 , 0.10404 , 0.25895 , -0.022912 , -0.28754 , -0.38468 , -0.089949 , -0.0050744 , 0.17039 , -0.318 , 0.40806 , 0.19729 , -0.47074 , -0.38096 , 0.47563 , -0.42267 , -0.36596 , 0.12273 , -0.092511 , -0.40519 , -0.084045 , 0.10114 , -0.3926 , -0.029798 , -0.2662 , -0.19559 , -0.075464 , 0.07131 , -0.48309 , -0.019021 , 0.49423 , 0.00028556 , 0.08106 , 0.19416 , 0.00084054 , 0.53115 , 0.069583 , 0.30878 , -0.16643 , -0.026291 , 0.38379 , 0.50059 , -0.53594 , -0.28638 , 0.37212 , -0.44905 , 0.44363 , 0.01414 , -0.31281 , 0.43897 , 0.090365 , -0.51925 , 0.17622 , 0.35899 , -0.388 , -0.036146 , 0.53654 , -0.1379 , 0.46033 , -0.36426 , -0.51956 , -0.084741 , 0.20375 , -0.20879 , -0.13447 , 0.34352 , -0.32432 , -0.20247 , -0.45219 , -0.3114 , 0.24505 , -0.083951 , 0.23035 , -0.30295 , 0.30972 , 0.028167 , -0.44292 , 0.41391 , -0.22493 , -0.12975 , -0.163 , -0.53987 , -0.21171 , -0.54145 , 0.12609 , -0.080698 , 0.040559 , -0.040591 , 0.41627 , -0.47606 , -0.25297 , 0.51085 , -0.20487 , 0.27565 , -0.42918 , -0.29596 , -0.24222 , 0.31079 , 0.052846 , -0.013232 , -0.10747 , 0.21718 , 0.49894 , -0.41927 , -0.36252 , 0.29682 , 0.48155 , 0.14915 , -0.098248 , -0.12913 , -0.32764 , 0.010045 , 0.24628 , -0.53413 , 0.065074 , 0.039831 , 0.31714 , 0.093487 , -0.22003 , 0.34886 , 0.37217 , 0.10217 , -0.53436 , -0.049081 , 0.52527 , 0.068685 , 0.27133 , 0.0031221 , 0.18593 , -0.45724 , -0.16345 , 0.39594 , -0.015962 , -0.069537 , 0.36635 , 0.52031 , -0.37068 , 0.32639 , 0.36991 , -0.3419 , -0.093731 , 0.3124 , -0.23413 , -0.28888 , -0.025687 , -0.27212 , 0.37024 , 0.21112 , -0.118 , -0.37629 , -0.41248 , 0.048335 , -0.41036 , -0.2483 , -0.14721 , -0.10204 , 0.36277 , -0.27307 , 0.27017 , -0.16687 , 0.079883 , 0.42454 , 0.44547 , -0.25542 , 0.21606 , 0.047524 , -0.26081 , -0.45067 , 0.28547 , 0.4304 , 0.27773 , 0.25735 , -0.057085 , -0.17188 , -0.059101 , 0.3709 , -0.54234 , -0.43161 , 0.035947 , 0.39347 , -0.052967 , 0.11991 , 0.28647 , 0.19851 , 0.44191 , -0.25738 , 0.097025 , 0.055415 , 0.45101 , -0.18302 , -0.4336 , -0.40715 , -0.26009 , 0.44376 , 0.22898 , 0.16317 , -0.049781 , -0.39171 , -0.45436 , 0.0063516 , -0.18887 , -0.44237 , -0.16966 , -0.16166 , 0.30487 , -0.26893 , 0.52784 , -0.4828 , -0.2379 , 0.38542 , 0.34065 , -0.13584 , -0.39507 , 0.292 , -0.064576 , 0.44992 , 0.38687 , 0.38762 , -0.13723 , 0.24304 , -0.25919 , -0.23592 , -0.16201 , -0.10797 , -0.064879 , 0.29997 , 0.35496 , 0.040786 , -0.35007 , 0.38789 , -0.15498 , -0.15759 , 0.07224 , -0.36945 , 0.18746 , -0.34249 , -0.36879 , -0.20154 , 0.061779 , -0.073078 , 0.19187 , -0.19955 , 0.37717 , -0.18949 , -0.54227 , 0.54145 , 0.2583 , -0.31814 , -0.21199 , 0.37992 , 0.15956 , -0.10309 , 0.2234 , 0.32783 , 0.3771 , -0.31839 , 0.17589 , -0.43926 , -0.098158 , -0.089941 , 0.020064 , 0.46082 , -0.27499 , 0.03183 , -0.47407 , 0.46537 , -0.003658 , 0.51691 , -0.50577 , -0.46885 , -0.49941 , 0.46406 , 0.48075 , -0.46346 , 0.48044 , 0.46013 , 0.45855 , 0.52394 , -0.48915 , -0.50106 , -0.51845 , 0.46587 , 0.46564 , -0.47473 , -0.47969 , 0.45766 , -0.47216 , 0.5172 , 0.45773 , -0.45855 , -0.53918 , 0.52593 , -0.53463 };
  double Zshift[299]  = { 0.5415 , -0.026175 , 0.38234 , -0.37879 , -0.031663 , -0.50704 , 0.24111 , 0.090023 , -0.091293 , -0.074906 , -0.2646 , 0.16727 , 0.064955 , -0.11888 , 0.37096 , -0.54272 , 0.34296 , 0.40407 , 0.51143 , -0.22603 , 0.22583 , -0.37372 , 0.42521 , -0.33813 , 0.28935 , 0.47852 , 0.45326 , -0.26711 , 0.24635 , -0.1562 , 0.43203 , 0.25527 , -0.45837 , 0.3046 , 0.24536 , 0.5239 , -0.21266 , 0.059282 , -0.3272 , 0.4344 , -0.039987 , 0.37979 , -0.08379 , 0.18575 , -0.27354 , 0.3139 , 0.12818 , -0.3746 , 0.18782 , 0.3387 , 0.28979 , 0.29479 , -0.38265 , 0.43713 , 0.50258 , 0.52507 , 0.37962 , 0.43927 , -0.3569 , -0.39338 , 0.33268 , -0.34848 , 0.1981 , -0.32482 , 0.40577 , 0.51918 , -0.052263 , -0.12362 , -0.17924 , -0.47367 , 0.43365 , -0.50578 , 0.40676 , 0.53135 , -0.2853 , -0.082201 , 0.51513 , 0.22755 , -0.12373 , 0.53182 , -0.36663 , 0.30579 , -0.099646 , -0.093709 , 0.1277 , -0.0054239 , 0.29654 , 0.37043 , 0.166 , 0.3242 , -0.52519 , -0.035496 , 0.17399 , -0.23772 , 0.01141 , -0.54485 , -0.53264 , 0.17363 , -0.10154 , 0.29367 , -0.0056675 , 0.18975 , -0.31213 , -0.46908 , -0.37156 , 0.18793 , -0.32041 , 0.25593 , -0.16684 , 0.20145 , 0.20993 , 0.11047 , -0.30298 , 0.54115 , -0.27183 , -0.47836 , -0.14523 , 0.51425 , 0.21178 , -0.50743 , -0.54139 , 0.14244 , -0.53099 , -0.24178 , -0.3699 , -0.24031 , 0.54045 , 0.43709 , 0.27353 , 0.039606 , 0.072539 , -0.46702 , 0.0050052 , 0.10811 , -0.48881 , -0.32163 , -0.0020008 , -0.16712 , -0.47333 , -0.0052957 , -0.43963 , -0.46954 , -0.035304 , 0.36634 , 0.40783 , -0.28039 , -0.36128 , 0.053035 , 0.27931 , 0.090446 , 0.46951 , 0.50602 , 0.052007 , -0.25658 , 0.050455 , 0.13301 , -0.27248 , -0.27492 , 0.035256 , -0.43586 , 0.18338 , -0.5343 , 0.17652 , 0.29816 , -0.17234 , 0.055155 , -0.0047934 , -0.037906 , -0.32944 , 0.38764 , -0.3552 , 0.3356 , -0.19353 , 0.24259 , -0.32704 , 0.078286 , 0.37657 , 0.05733 , 0.14018 , -0.43498 , 0.51929 , -0.017455 , -0.086105 , 0.094388 , 0.52401 , -0.54389 , -0.54091 , -0.41362 , -0.43836 , 0.015585 , 0.14916 , -0.47846 , -0.38079 , -0.22913 , 0.041096 , -0.20817 , 0.39094 , 0.5437 , 0.0048242 , -0.43728 , -0.5396 , -0.069328 , -0.1615 , -0.46176 , -0.14909 , 0.28491 , 0.41844 , -0.47852 , 0.36699 , 0.477 , 0.4616 , -0.11209 , 0.023602 , 0.1294 , 0.043565 , -0.35396 , 0.002009 , -0.14754 , -0.52797 , -0.25148 , -0.22665 , -0.35621 , 0.16845 , -0.21548 , -0.21882 , -0.24656 , -0.38865 , 0.45176 , -0.18102 , 0.53679 , -0.28183 , 0.52386 , 0.4389 , 0.47522 , -0.34161 , 0.48019 , -0.4894 , -0.34372 , -0.16902 , -0.39673 , 0.48618 , -0.19908 , 0.38465 , 0.19825 , 0.24221 , 0.34745 , 0.54175 , -0.28974 , -0.25584 , 0.047639 , -0.22256 , 0.44844 , -0.39822 , 0.35743 , -0.14659 , -0.077251 , 0.25557 , -0.40132 , 0.30568 , -0.11616 , 0.24221 , 0.065132 , 0.16769 , -0.19437 , -0.056612 , 0.37653 , -0.41642 , -0.27579 , -0.3475 , 0.25428 , -0.40994 , -0.53469 , -0.30806 , 0.24536 , -0.21266 , 0.37979 , -0.3746 , 0.18782 , 0.43927 , 0.1981 , -0.052263 , 0.37043 , 0.3242 , -0.54485 , 0.17363 , -0.16684 , -0.30298 , -0.50743 , 0.27353 , 0.072539 , -0.46954 , -0.086105 , 0.023602 , 0.1294 , -0.22256 , 0.44844 , -0.27579 , -0.40994 , -0.53469 };
  double Majaxis[299] = { 0.020004 , 0.02004 , 0.020062 , 0.02011 , 0.020123 , 0.020139 , 0.020181 , 0.020182 , 0.02026 , 0.020279 , 0.020296 , 0.020363 , 0.020363 , 0.020375 , 0.020402 , 0.020422 , 0.020423 , 0.020437 , 0.02046 , 0.020466 , 0.020469 , 0.020523 , 0.020523 , 0.020526 , 0.020548 , 0.020586 , 0.020612 , 0.020696 , 0.020771 , 0.020806 , 0.020844 , 0.020865 , 0.020978 , 0.021012 , 0.021104 , 0.021143 , 0.021148 , 0.02121 , 0.021257 , 0.021287 , 0.021329 , 0.021394 , 0.021405 , 0.021414 , 0.021479 , 0.021621 , 0.021632 , 0.021655 , 0.021672 , 0.021705 , 0.021718 , 0.021849 , 0.02188 , 0.021911 , 0.021912 , 0.022019 , 0.022112 , 0.022149 , 0.022181 , 0.022192 , 0.022249 , 0.022271 , 0.022402 , 0.022414 , 0.022494 , 0.022507 , 0.022762 , 0.022839 , 0.022917 , 0.022925 , 0.022981 , 0.022983 , 0.023031 , 0.02304 , 0.023091 , 0.023163 , 0.023312 , 0.023338 , 0.023453 , 0.023519 , 0.023569 , 0.023595 , 0.023677 , 0.02368 , 0.023704 , 0.023793 , 0.023798 , 0.023855 , 0.023909 , 0.02392 , 0.023965 , 0.023975 , 0.024004 , 0.024045 , 0.024291 , 0.024353 , 0.024388 , 0.024492 , 0.024604 , 0.024626 , 0.024644 , 0.024752 , 0.02477 , 0.024776 , 0.024881 , 0.024971 , 0.025214 , 0.025216 , 0.025264 , 0.025365 , 0.02539 , 0.025435 , 0.025443 , 0.025617 , 0.025749 , 0.025759 , 0.025759 , 0.02576 , 0.025769 , 0.025815 , 0.025948 , 0.026073 , 0.026118 , 0.026124 , 0.026274 , 0.026405 , 0.026577 , 0.026608 , 0.026732 , 0.026777 , 0.026902 , 0.026943 , 0.026962 , 0.027083 , 0.027125 , 0.027125 , 0.027209 , 0.027313 , 0.027426 , 0.027528 , 0.027584 , 0.027658 , 0.02772 , 0.02776 , 0.027777 , 0.027796 , 0.027838 , 0.027882 , 0.027914 , 0.027935 , 0.028 , 0.028058 , 0.02836 , 0.028375 , 0.028442 , 0.0285 , 0.028504 , 0.028511 , 0.028559 , 0.028733 , 0.028799 , 0.028827 , 0.029037 , 0.029057 , 0.029218 , 0.02924 , 0.029269 , 0.02933 , 0.02935 , 0.029397 , 0.029459 , 0.029526 , 0.029534 , 0.029655 , 0.029803 , 0.029817 , 0.029966 , 0.030027 , 0.030029 , 0.030087 , 0.030087 , 0.030147 , 0.030235 , 0.030247 , 0.030314 , 0.030408 , 0.030571 , 0.030698 , 0.030702 , 0.030719 , 0.030815 , 0.030821 , 0.030984 , 0.031028 , 0.031106 , 0.031114 , 0.031309 , 0.031337 , 0.031502 , 0.031505 , 0.031629 , 0.031913 , 0.032007 , 0.032405 , 0.032518 , 0.032618 , 0.032664 , 0.03268 , 0.032684 , 0.033117 , 0.033188 , 0.033196 , 0.033267 , 0.03352 , 0.033834 , 0.033843 , 0.034007 , 0.034245 , 0.03437 , 0.034668 , 0.03473 , 0.034838 , 0.035036 , 0.035053 , 0.035149 , 0.035409 , 0.03557 , 0.03572 , 0.035747 , 0.0358 , 0.035874 , 0.036028 , 0.036202 , 0.036219 , 0.036401 , 0.036418 , 0.036456 , 0.036511 , 0.03658 , 0.036974 , 0.037067 , 0.037142 , 0.037223 , 0.03731 , 0.037346 , 0.037352 , 0.037377 , 0.037485 , 0.037835 , 0.038909 , 0.039492 , 0.039608 , 0.039689 , 0.039796 , 0.039898 , 0.039994 , 0.040015 , 0.040017 , 0.040172 , 0.040309 , 0.040405 , 0.040516 , 0.041238 , 0.041243 , 0.041777 , 0.042256 , 0.042554 , 0.042737 , 0.042815 , 0.042964 , 0.043061 , 0.043634 , 0.043867 , 0.021104 , 0.021148 , 0.021394 , 0.021655 , 0.021672 , 0.022149 , 0.022402 , 0.022762 , 0.023855 , 0.02392 , 0.024353 , 0.024492 , 0.025264 , 0.025443 , 0.025815 , 0.026732 , 0.026902 , 0.027658 , 0.030235 , 0.033267 , 0.03352 , 0.039492 , 0.039608 , 0.042737 , 0.043061 , 0.043634 };
  double Minaxis[299] = { 0.014327 , 0.0099816 , 0.0079475 , 0.0067382 , 0.0092416 , 0.0054686 , 0.0079646 , 0.01336 , 0.012604 , 0.013941 , 0.015507 , 0.006454 , 0.0055965 , 0.010408 , 0.013413 , 0.0097163 , 0.015056 , 0.0061028 , 0.0077156 , 0.0051759 , 0.017189 , 0.0052982 , 0.0096657 , 0.01076 , 0.012129 , 0.012807 , 0.0076778 , 0.006741 , 0.0060004 , 0.0056357 , 0.0053628 , 0.016735 , 0.0052267 , 0.0057199 , 0.0083263 , 0.0094517 , 0.012813 , 0.01103 , 0.0098089 , 0.013574 , 0.006371 , 0.012738 , 0.0073692 , 0.013902 , 0.011126 , 0.0098853 , 0.0080003 , 0.0064415 , 0.0066103 , 0.012389 , 0.0060653 , 0.0087545 , 0.010981 , 0.0092382 , 0.015435 , 0.0096992 , 0.011574 , 0.0080925 , 0.011675 , 0.012981 , 0.015948 , 0.015128 , 0.010294 , 0.0080096 , 0.0051034 , 0.010367 , 0.011007 , 0.010025 , 0.005869 , 0.0055645 , 0.0075996 , 0.0079119 , 0.0055819 , 0.0063155 , 0.0088309 , 0.01453 , 0.0050177 , 0.0053662 , 0.010173 , 0.0082155 , 0.0074167 , 0.006434 , 0.015945 , 0.0077343 , 0.0095707 , 0.016882 , 0.013134 , 0.0059642 , 0.0065564 , 0.015614 , 0.017264 , 0.0075763 , 0.006793 , 0.0051688 , 0.01707 , 0.006315 , 0.010919 , 0.0079502 , 0.0096913 , 0.0082356 , 0.0092863 , 0.0052858 , 0.016991 , 0.011849 , 0.0063774 , 0.010478 , 0.012739 , 0.0069143 , 0.01976 , 0.0086271 , 0.009269 , 0.0091104 , 0.0062468 , 0.01799 , 0.012409 , 0.0053492 , 0.0077024 , 0.0050801 , 0.012564 , 0.0075616 , 0.016538 , 0.0069052 , 0.014742 , 0.0055335 , 0.010662 , 0.0087099 , 0.0092536 , 0.010254 , 0.010465 , 0.0065039 , 0.0055155 , 0.019832 , 0.0089958 , 0.0098236 , 0.018973 , 0.007204 , 0.010104 , 0.01323 , 0.014672 , 0.010585 , 0.0058373 , 0.011372 , 0.013203 , 0.0099765 , 0.0070372 , 0.010354 , 0.0055951 , 0.0060131 , 0.013103 , 0.0079449 , 0.0051299 , 0.005036 , 0.010246 , 0.012704 , 0.0057771 , 0.014115 , 0.014807 , 0.0052778 , 0.0084248 , 0.0096462 , 0.0055434 , 0.0095333 , 0.011269 , 0.01221 , 0.012258 , 0.0067901 , 0.006454 , 0.012845 , 0.014736 , 0.010879 , 0.0083323 , 0.0077235 , 0.0051711 , 0.0069054 , 0.017363 , 0.014372 , 0.0072299 , 0.0063376 , 0.010933 , 0.018564 , 0.0061667 , 0.012848 , 0.0064541 , 0.0058952 , 0.0051857 , 0.0072317 , 0.0078115 , 0.0099858 , 0.010605 , 0.013646 , 0.014084 , 0.0094785 , 0.012782 , 0.010161 , 0.007457 , 0.0051096 , 0.0067752 , 0.0070392 , 0.0055331 , 0.013437 , 0.013798 , 0.0061589 , 0.0051074 , 0.015242 , 0.0051894 , 0.0077062 , 0.010107 , 0.010847 , 0.013242 , 0.0052751 , 0.010423 , 0.0070397 , 0.017173 , 0.0094386 , 0.0074332 , 0.0064722 , 0.0092312 , 0.0059999 , 0.0067572 , 0.010947 , 0.008076 , 0.0054722 , 0.0081541 , 0.0082725 , 0.01725 , 0.0089949 , 0.011478 , 0.017171 , 0.0071159 , 0.006895 , 0.011438 , 0.0068836 , 0.008132 , 0.01367 , 0.0088901 , 0.0059138 , 0.0081291 , 0.0059966 , 0.0086854 , 0.013832 , 0.0068204 , 0.005614 , 0.0096036 , 0.014077 , 0.010208 , 0.0060625 , 0.0052894 , 0.011616 , 0.0050841 , 0.0068374 , 0.0096471 , 0.012576 , 0.016383 , 0.0090394 , 0.0075459 , 0.0057784 , 0.0060681 , 0.013247 , 0.0057273 , 0.0099803 , 0.0070866 , 0.0066253 , 0.007665 , 0.0064052 , 0.010079 , 0.0076156 , 0.0070544 , 0.0063735 , 0.0060472 , 0.0063675 , 0.0062031 , 0.0060378 , 0.0056123 , 0.0083263 , 0.012813 , 0.012738 , 0.0064415 , 0.0066103 , 0.0080925 , 0.010294 , 0.011007 , 0.0059642 , 0.015614 , 0.006315 , 0.0079502 , 0.01976 , 0.0062468 , 0.0075616 , 0.010465 , 0.0055155 , 0.011372 , 0.0064541 , 0.017173 , 0.0094386 , 0.0096471 , 0.012576 , 0.0063735 , 0.0062031 , 0.0060378 };
  double Angle[299]   = { 1.4558 , 1.0249 , 0.91246 , 3.7799 , 1.4959 , 1.7974 , 5.3369 , 5.7376 , 3.5275 , 2.1432 , 3.5593 , 4.3224 , 2.7564 , 1.51 , 4.5466 , 3.919 , 5.4015 , 0.30619 , 0.67212 , 3.5822 , 6.238 , 5.3461 , 5.0576 , 5.0017 , 2.834 , 6.059 , 2.9888 , 3.6527 , 1.3913 , 1.8141 , 4.7455 , 1.4383 , 1.1027 , 1.1936 , 0.59347 , 1.7009 , 3.6973 , 4.8118 , 1.848 , 2.8246 , 1.5613 , 5.2432 , 5.4165 , 5.8815 , 5.5182 , 5.4343 , 2.1553 , 3.0717 , 6.1326 , 3.7169 , 4.8459 , 1.3129 , 0.15237 , 5.8569 , 5.9889 , 0.86512 , 1.9941 , 2.5237 , 5.433 , 0.58891 , 1.7834 , 1.4294 , 4.8015 , 2.0355 , 1.9812 , 0.89478 , 4.4992 , 1.1769 , 4.2821 , 2.4354 , 4.3865 , 2.0177 , 0.76227 , 4.8369 , 2.8215 , 1.646 , 4.3235 , 4.5098 , 2.9366 , 5.7934 , 4.8433 , 0.20172 , 5.7323 , 3.9258 , 0.23259 , 1.5851 , 5.3528 , 5.6937 , 3.1197 , 4.6992 , 1.5269 , 2.9197 , 5.9799 , 3.9698 , 5.1291 , 0.46843 , 0.32144 , 1.3667 , 3.6631 , 4.3596 , 5.3843 , 5.0461 , 2.8384 , 0.4362 , 4.9122 , 0.91605 , 2.291 , 2.334 , 3.6956 , 3.0292 , 1.1774 , 0.82064 , 1.6694 , 3.2481 , 4.5823 , 2.4318 , 4.2287 , 4.6383 , 4.3096 , 6.0267 , 4.974 , 2.5711 , 5.7808 , 0.86595 , 1.9546 , 1.169 , 0.94583 , 1.6645 , 4.3546 , 4.9469 , 4.3364 , 2.9925 , 0.19103 , 1.8663 , 1.8633 , 3.596 , 1.4591 , 1.9571 , 4.8912 , 6.009 , 4.9117 , 1.4427 , 1.1956 , 3.8217 , 1.4041 , 0.48615 , 5.4622 , 2.4336 , 4.6307 , 1.4259 , 2.5079 , 4.2249 , 0.23295 , 4.5866 , 1.6253 , 3.0094 , 5.5111 , 2.2686 , 4.7023 , 2.9195 , 5.0689 , 5.6642 , 4.5094 , 4.5253 , 1.6656 , 4.3838 , 1.1062 , 6.1138 , 0.32075 , 3.4346 , 4.1934 , 6.0929 , 2.803 , 1.7798 , 1.4638 , 1.1769 , 1.6757 , 3.5648 , 5.805 , 1.7655 , 1.869 , 3.4948 , 5.0538 , 0.5722 , 5.2496 , 0.74496 , 0.93514 , 3.845 , 4.0066 , 1.4639 , 0.98186 , 1.6919 , 0.41886 , 5.0204 , 4.4884 , 1.6724 , 2.3402 , 4.468 , 5.6256 , 5.7988 , 4.1419 , 4.5061 , 2.1176 , 6.0354 , 5.7664 , 3.1422 , 4.2172 , 5.2365 , 5.3768 , 1.6359 , 0.86165 , 4.5322 , 4.5114 , 4.4432 , 4.5294 , 5.1042 , 3.9791 , 1.1958 , 1.8184 , 4.6404 , 1.1193 , 2.8933 , 1.0764 , 2.3314 , 4.668 , 5.0065 , 2.2973 , 5.637 , 1.2619 , 2.4728 , 4.9948 , 2.4295 , 0.80222 , 3.4089 , 1.3484 , 1.6781 , 5.9017 , 2.6379 , 2.663 , 5.0669 , 1.9895 , 3.4627 , 2.2352 , 0.15207 , 0.62638 , 6.1007 , 1.1807 , 5.8529 , 4.8815 , 1.5408 , 1.4216 , 4.0129 , 3.5676 , 0.60916 , 0.28774 , 3.7289 , 5.2765 , 1.9752 , 4.8562 , 2.3279 , 5.9472 , 4.7341 , 0.67569 , 2.1298 , 6.1253 , 1.1864 , 5.4152 , 0.9864 , 0.21133 , 0.53214 , 2.5471 , 1.9962 , 1.5181 , 0.59347 , 3.6973 , 5.2432 , 3.0717 , 6.1326 , 2.5237 , 4.8015 , 4.4992 , 5.6937 , 4.6992 , 0.46843 , 1.3667 , 3.6956 , 1.6694 , 6.0267 , 4.3546 , 4.3364 , 1.4427 , 5.0538 , 4.5114 , 4.4432 , 1.4216 , 4.0129 , 0.9864 , 2.5471 , 1.9962 };

  // bool isInsideSomeEllipse = false;
  // bool isInsideThisEllipse = false;
  // for (int i = 0; i < nellipses; ++i) {
  //   isInsideThisEllipse = ((coordinates.x - Xshift[i])*cos(Angle[i]) + (coordinates.z - Zshift[i])*sin(Angle[i]))*((coordinates.x - Xshift[i])*cos(Angle[i]) + (coordinates.z - Zshift[i])*sin(Angle[i]))/(Majaxis[i] * Majaxis[i]) + (-(coordinates.z - Zshift[i])*cos(Angle[i]) + (coordinates.x - Xshift[i])*sin(Angle[i]))*(-(coordinates.z - Zshift[i])*cos(Angle[i]) + (coordinates.x - Xshift[i])*sin(Angle[i]))/ (Minaxis[i] * Minaxis[i]) < 1; // rotated ellipse
  //   // reminder ellipse function: inside = [(x-x0)*cos(phi)+(z-z0)*sin(phi)]^2/majaxis^2 + [(x-x0)*sin(phi)-(z-z0)*cos(phi)]^2/minaxis^2 < 1
  //   if (isInsideThisEllipse) {
  //     isInsideSomeEllipse = true;
  //     return Angle[i] * 180.0 / M_PI + 90; // corresponding aniso_angle
  //   }
  // }
  // if (!isInsideSomeEllipse) {
  //   //return 135; // fixed value in matrix
    double angle = rand() / (double)RAND_MAX * 360.0;
    // printf("%.03lf\n", angle);
    return angle; // random value in matrix
  // }
}

int main(int nargs, char *args[]) {
  // Input file name
  char *input_file;
  if ( nargs < 2 ) {
    asprintf(&input_file, "AnisoViscTest_HomoRandomAngle.txt"); // Default
  }
  else {
    asprintf(&input_file, "%s", args[1]);     // Custom
  }
  printf("Running MDoodz7.0 using %s\n", input_file);
  MdoodzSetup setup = {
          .SetParticles  = &(SetParticles_ff){
                   .SetPhase              = SetPhase,
                   .SetDensity            = SetDensity,
                   .SetAnisoAngle         = SetAnisoAngle,
          },
          .SetBCs = &(SetBCs_ff){
                  .SetBCVx = SetPureOrSimpleShearBCVx,
                  .SetBCVz = SetPureOrSimpleShearBCVz,
          },
  };
  RunMDOODZ(input_file, &setup);
  free(input_file);
}
